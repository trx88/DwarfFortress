#include "World.h"
#include <fstream>
#include "../../DataModels/WorldDataModel.h"
#include "../../Domains/Entities/Entity.h"
#include "../../Domains/Entities/Player.h"
#include "../../Domains/Entities/Enemy.h"
#include <iostream>

World::World()
{
	worldData = std::make_unique<WorldDataModel>();
}

World::~World()
{
}

bool World::InitializeFromJSON(const std::string& filePath)
{
    try
    {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath);
        }

        nlohmann::json jsonData;
        //std::cout << file;
        file >> jsonData;

        worldData->SetMapSize(jsonData["width"], jsonData["height"]);
        parseMap(jsonData["map"]);
        parseEntities(jsonData["entities"]);

        return true;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        // Handle the exception as needed
        return false;
    }
}

void World::parseMap(const nlohmann::json& mapData)
{
    for (int y = 0; y < worldData->GetHeight(); ++y)
    {
        for (int x = 0; x < worldData->GetWidth(); ++x)
        {
            worldData->SetTileAt(y, x, mapData[y][x].get<std::string>()[0]);
        }
    }

    //onWorldDataUpdated(worldData.get());
}

void World::parseEntities(const nlohmann::json& entitiesData)
{
    // Parse player
    auto playerData = entitiesData["player"];
    auto playerStatsData = playerData["stats"];
    auto player = std::make_shared<Player>(
        worldData->GetEntityNextId(), 
        playerData["type"], 
        playerData["row"], 
        playerData["column"],
        playerStatsData["health"],
        playerStatsData["armor"],
        playerStatsData["damage"]);
    worldData->AddEntity(player);

    // Parse enemies
    for (const auto& enemyData : entitiesData["enemies"])
    {
        auto enemyStatsData = enemyData["stats"];
        auto enemy = std::make_shared<Entity>(
            worldData->GetEntityNextId(), 
            enemyData["type"], 
            enemyData["row"], 
            enemyData["column"],
            enemyStatsData["health"],
            enemyStatsData["armor"],
            enemyStatsData["damage"]);
        worldData->AddEntity(enemy);
    }

    // Parse obstacles
    for (const auto& obstaclesData : entitiesData["obstacles"])
    {
        auto obstacles = std::make_shared<Entity>(worldData->GetEntityNextId(), obstaclesData["type"], obstaclesData["row"], obstaclesData["column"]);
        worldData->AddEntity(obstacles);
    }

    // Parse chests
    for (const auto& chestData : entitiesData["chests"])
    {
        auto chest = std::make_shared<Entity>(worldData->GetEntityNextId(), chestData["type"], chestData["row"], chestData["column"]);
        worldData->AddEntity(chest);
        // Optionally store chest contents if needed
    }
}

bool World::IsTileValidForMovement(int row, int column) const
{
    if (row < 0 || row >= worldData->GetHeight() || column < 0 || column >= worldData->GetWidth())
    {
        //Out of bounds!
        return false;
    }

    auto entity = worldData->GetEntityAt(row, column);
    if (entity) 
    {
        // Check if the entity is something that should block movement
        //Enemy should not block movement (at least in my mind), instead battle should ensue. 
        if (entity->GetType() == static_cast<int>(EntityType::Mountain) ||
            entity->GetType() == static_cast<int>(EntityType::Tree))
        {
            return false; // Block movement
        }
        // If it's a chest or another non-blocking entity, allow movement
        return true;
    }
    // No entity at this position, so it's not occupied
    return true;
}

bool World::MoveEntity(std::shared_ptr<Entity> entity, int newRow, int newColumn)
{
    int oldRow = entity->GetRow();
    int oldColumn = entity->GetColumn();

    if (IsTileValidForMovement(newRow, newColumn))
    {
        auto targetEntity = worldData->GetEntityAt(newRow, newColumn);
        if (targetEntity && targetEntity->GetType() == static_cast<int>(EntityType::Chest)) 
        {
            //TODO: Pick up item. Enemy skips the chest.
            //auto player = std::static_pointer_cast<Player>(entity);
            //if (player) {
            //    player->pickUpItemsFrom(targetEntity);
            //    //removeEntity(targetEntity); // Remove chest after looting
            //}
        }

        // Enemy leaves the chest in place
        if (entity->GetType() == static_cast<int>(EntityType::Enemy))
        {
            auto entityAtOldPosition = worldData->GetEntityAt(oldRow, oldColumn);
            if (entityAtOldPosition && entityAtOldPosition->GetType() == static_cast<int>(EntityType::Chest))
            {
                worldData->SetTileAt(oldRow, oldColumn, targetEntity->GetTileSymbol());
            }
            else
            {
                // Clear the old position by setting it to an empty tile
                worldData->SetTileAt(oldRow, oldColumn, '.');
            }
        }
        else
        {
            // Clear the old position by setting it to an empty tile for any other case
            worldData->SetTileAt(oldRow, oldColumn, '.');
        }

        // Update entity position
        entity->SetPosition(newRow, newColumn);

        // Emit signal indicating the entity has moved
        //onWorldDataUpdated(worldData.get());
        SignalWorldUpdate();

        return true;
    }

    return false;
}

std::shared_ptr<Player> World::GetPlayer()
{
    return std::static_pointer_cast<Player>(worldData->GetEntitiesByType(EntityType::Player).back());
}

std::vector<std::shared_ptr<Enemy>> World::GetEnemies()
{
    std::vector<std::shared_ptr<Enemy>> enemies;
    for (const auto& enemy : worldData->GetEntitiesByType(EntityType::Enemy))
    {
        enemies.push_back(std::static_pointer_cast<Enemy>(enemy));
    }

    return enemies;
}

void World::SignalWorldUpdate()
{
    onWorldDataUpdated(worldData.get());
}
