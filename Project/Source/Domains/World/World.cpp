#include "World.h"
#include <fstream>
#include "../../DataModels/WorldDataModel.h"
#include "../../Domains/Entities/Entity.h"

World::World()
{
	worldData = std::make_unique<WorldDataModel>();
}

World::~World()
{
}

bool World::initializeFromJSON(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    nlohmann::json jsonData;
    file >> jsonData;

    worldData->SetMapSize(jsonData["width"], jsonData["height"]);

    return true;
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
