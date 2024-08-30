#include "World.h"
#include <fstream>
#include "../../DataModels/WorldDataModel.h"
#include "../../Domains/Entities/Entity.h"
#include "../../Domains/Entities/Player.h"
#include <iostream>

World::World()
{
	worldData = std::make_unique<WorldDataModel>();
}

World::~World()
{
}

bool World::initializeFromJSON(const std::string& filePath)
{
    try
    {
        std::string test = "I:\\Playrix\\PlayrixDwarfFortress\\Project\\Data\\World.json";
        /*std::ifstream file(filePath);*/
        std::ifstream file(test);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath);
        }

        nlohmann::json jsonData;
        //std::cout << file;
        file >> jsonData;

        worldData->SetMapSize(jsonData["width"], jsonData["height"]);
        parseMap(jsonData["map"]);
        parseEntities(jsonData["entities"]);

        onWorldDataUpdated(worldData.get());

        return true;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        // Handle the exception as needed
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
            //TODO: Pick up item
            //auto player = std::static_pointer_cast<Player>(entity);
            //if (player) {
            //    player->pickUpItemsFrom(targetEntity);
            //    //removeEntity(targetEntity); // Remove chest after looting
            //}
        }

        // Clear the old position by setting it to an empty tile
        worldData->SetTileAt(oldRow, oldColumn, '.');

        // Update entity position
        entity->SetPosition(newRow, newColumn);

        // Emit signal indicating the entity has moved
        onWorldDataUpdated(worldData.get());

        return true;
    }

    return false;
}

std::shared_ptr<Player> World::GetPlayer()
{
    return std::static_pointer_cast<Player>(worldData->GetEntityById(1));
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
    auto player = std::make_shared<Entity>(worldData->GetEntityNextId(), playerData["type"], playerData["row"], playerData["column"]);
    worldData->AddEntity(player);

    // Parse enemies
    for (const auto& enemyData : entitiesData["enemies"])
    {
        auto enemy = std::make_shared<Entity>(worldData->GetEntityNextId(), enemyData["type"], enemyData["row"], enemyData["column"]);
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
