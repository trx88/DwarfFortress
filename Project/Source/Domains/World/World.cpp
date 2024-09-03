#include "World.h"
#include <fstream>
#include "../../DataModels/WorldDataModel.h"
#include "../../Domains/Entities/Entity.h"
#include "../../Domains/Entities/Player.h"
#include "../../Domains/Entities/Enemy.h"
#include <iostream>
#include "../Entities/Chest.h"

World::World()
{
	worldData = std::make_unique<WorldDataModel>();
}

World::~World()
{
}

nlohmann::json World::MapToJSON()
{
    nlohmann::json jsonData;
    jsonData["width"] = worldData->GetWidth();
    jsonData["height"] = worldData->GetHeight();

    for (int row = 0; row < worldData->GetHeight(); row++)
    {
        nlohmann::json jRow = nlohmann::json::array();
        for (int column = 0; column < worldData->GetWidth(); column++)
        {
            auto entity = worldData->GetEntityAt(row, column);
            if (entity)
            {
                jRow.push_back(std::string(1, entity->GetTileSymbol())); // Store as a single-character string
            }
            else
            {
                jRow.push_back(std::string(1, '.')); // Store as a single-character string
            }
        }
        jsonData["map"].push_back(jRow);
    }

    return jsonData;
}

bool World::InitializeFromJSON(const std::string& filePath)
{
    try
    {
        std::ifstream file(filePath);
        if (!file.is_open()) 
        {
            throw std::runtime_error("Could not open file: " + filePath);
        }

        nlohmann::json jsonData;
        file >> jsonData;

        worldData->ClearEntities();
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
}

void World::parseEntities(const nlohmann::json& entitiesData)
{
    // Parse player
    auto playerData = entitiesData["player"];
    auto playerStatsData = playerData["stats"];
    auto playerInventoryData = playerData["inventory"];

    auto player = std::make_shared<Player>(
        worldData->GetEntityNextId(), 
        static_cast<EntityType>(playerData["type"]),
        playerData["row"], 
        playerData["column"],
        playerStatsData["health"],
        playerStatsData["armor"],
        playerStatsData["damage"]);
    
    //Default inventory
    for (auto const& items : playerInventoryData)
    {
        player->AccessInventory()->StoreItem(std::make_shared<Item>(
            items["name"],
            items["type"],
            items["modifier"],
            items["stacks"]));
    }
    player->SwapWeapons();//Equip unarmed

    worldData->AddEntity(player);

    // Parse enemies
    for (const auto& enemyData : entitiesData["enemies"])
    {
        auto enemyStatsData = enemyData["stats"];
        auto enemy = std::make_shared<Enemy>(
            worldData->GetEntityNextId(), 
            static_cast<EntityType>(enemyData["type"]),
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
        auto obstacles = std::make_shared<Entity>(worldData->GetEntityNextId(), static_cast<EntityType>(obstaclesData["type"]), obstaclesData["row"], obstaclesData["column"]);
        worldData->AddEntity(obstacles);
    }

    // Parse chests
    for (const auto& chestData : entitiesData["chests"])
    {
        auto chestContents = chestData["contents"];
        
        std::vector<std::shared_ptr<Item>> items;
        for (const auto& content : chestContents)
        {
            items.push_back(std::make_shared<Item>(
                content["name"],
                content["type"],
                content["modifier"],
                content["stacks"]
            ));
        }

        auto chest = std::make_shared<Chest>(worldData->GetEntityNextId(), static_cast<EntityType>(chestData["type"]), chestData["row"], chestData["column"], items);
        worldData->AddEntity(chest);
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
        //Enemy should not block movement (at least in my mind), instead battle should ensue. 
        if (entity->GetType() == EntityType::Mountain ||
            entity->GetType() == EntityType::Tree)
        {
            return false; // Block movement
        }
        //If it's a chest or another non-blocking entity, allow movement
        return true;
    }
    //No entity at this position, so it's not occupied
    return true;
}

bool World::MoveEntity(std::shared_ptr<Entity> entity, int newRow, int newColumn)
{
    int oldRow = entity->GetRow();
    int oldColumn = entity->GetColumn();

    if (IsTileValidForMovement(newRow, newColumn))
    {
        auto targetEntity = worldData->GetEntityAt(newRow, newColumn);
        if (targetEntity && targetEntity->GetType() == EntityType::Chest && entity->GetType() == EntityType::Player)
        {
            auto player = std::static_pointer_cast<Player>(entity);
            if (player) {
                player->OpenChestAndStoreItems(std::static_pointer_cast<Chest>(targetEntity));
                worldData->RemoveEntity(targetEntity);
            }
        }

        //Enemy leaves the chest in place
        if (entity->GetType() == EntityType::Enemy)
        {
            auto entityAtOldPosition = worldData->GetEntityAt(oldRow, oldColumn);
            if (entityAtOldPosition && entityAtOldPosition->GetType() == EntityType::Chest)
            {
                worldData->SetTileAt(oldRow, oldColumn, targetEntity->GetTileSymbol());
            }
            else
            {
                //Clear the old position by setting it to an empty tile
                worldData->SetTileAt(oldRow, oldColumn, '.');
            }
        }
        else
        {
            //Clear the old position by setting it to an empty tile for any other case
            worldData->SetTileAt(oldRow, oldColumn, '.');
        }

        //Update entity position
        entity->SetPosition(newRow, newColumn);

        //Emit signal indicating the entity has moved
        SignalWorldUpdate();

        return true;
    }

    return false;
}

std::shared_ptr<Player> World::GetPlayer()
{
    return std::static_pointer_cast<Player>(worldData->GetEntitiesByType(EntityType::Player).back());
}

std::vector<std::shared_ptr<class Enemy>> World::GetEnemiesAtPosition(int row, int column)
{
    std::vector<std::shared_ptr<Enemy>> enemies;
    for (const auto& enemy : worldData->GetEntitiesByType(EntityType::Enemy))
    {
        if (enemy->GetRow() == row && enemy->GetColumn() == column)
        {
            enemies.push_back(std::static_pointer_cast<Enemy>(enemy));
        }
    }

    return enemies;
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

std::vector<std::shared_ptr<class Chest>> World::GetChests()
{
    std::vector<std::shared_ptr<Chest>> chests;
    for (const auto& chest : worldData->GetEntitiesByType(EntityType::Chest))
    {
        chests.push_back(std::static_pointer_cast<Chest>(chest));
    }

    return chests;
}

std::vector<std::shared_ptr<class Entity>> World::GetObstacles()
{
    std::vector<std::shared_ptr<Entity>> obstacles;
    for (const auto& mountain : worldData->GetEntitiesByType(EntityType::Mountain))
    {
        obstacles.push_back(mountain);
    }
    for (const auto& tree : worldData->GetEntitiesByType(EntityType::Tree))
    {
        obstacles.push_back(tree);
    }

    return obstacles;
}

void World::RemoveFromWorld(std::shared_ptr<Entity> entity)
{
    worldData->RemoveEntity(entity);
    SignalWorldUpdate();
}

void World::SignalWorldUpdate()
{
    onWorldDataUpdated(worldData.get());
}
