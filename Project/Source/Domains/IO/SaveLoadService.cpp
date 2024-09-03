#include "SaveLoadService.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "../World/World.h"
#include "../../Domains/Entities/Player.h"
#include "../../Domains/Entities/Enemy.h"
#include "../../Domains/Entities/Chest.h"

SaveLoadService::SaveLoadService()
{
}

SaveLoadService::~SaveLoadService()
{
}

bool SaveLoadService::SaveToJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player)
{
    nlohmann::json jsonData;

    jsonData = world->MapToJSON();//Contains width, height and map tiles. ADD TO THIS!
    nlohmann::json jsonEntities;
    nlohmann::json jsonEntitiesEnemies = nlohmann::json::array();
    nlohmann::json jsonEntitiesObstacles = nlohmann::json::array();
    nlohmann::json jsonEntitiesChests = nlohmann::json::array();
    nlohmann::json jsonPlayerObject = nlohmann::json::object();

    jsonPlayerObject = world->GetPlayer()->PlayerToJSON();
    jsonEntities["player"] = jsonPlayerObject;

    for (const auto& enemy : world->GetEnemies())
    {
        jsonEntitiesEnemies.push_back(std::static_pointer_cast<Enemy>(enemy)->EnemyToJSON());
    }
    jsonEntities["enemies"] = jsonEntitiesEnemies;

    for (const auto& obstacle : world->GetObstacles())
    {
        jsonEntitiesObstacles.push_back(obstacle->EntityToJSON());
    }
    jsonEntities["obstacles"] = jsonEntitiesObstacles;

    for (const auto& chest : world->GetChests())
    {
        jsonEntitiesChests.push_back(std::static_pointer_cast<Chest>(chest)->ChestToJSON());
    }
    jsonEntities["chests"] = jsonEntitiesChests;

    jsonData["entities"] = jsonEntities;

    std::ofstream file("Save.json", std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        std::cerr << "Unable to open or create file for writing: " << "save.json" << std::endl;
    }

    try
    {
        file << jsonData.dump(4);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error writing JSON to file: " << e.what() << std::endl;
    }
    file.close();

    if (file.fail())
    {
        std::cerr << "Failed to write to file: " << "save.json" << std::endl;
        return false;
    }
    else
    {
        std::cout << "World data saved successfully to " << "save.json" << std::endl;
        return true;
    }
}

[[deprecated("Not used, since there's LoadGame from Game can be used for this.")]]
bool SaveLoadService::LoadFromJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player)
{
    if (world->InitializeFromJSON("save.json"))
    {
        world->SignalWorldUpdate();
        player->SignalPlayerStatsUpdate();
        player->AccessInventory()->SignalInventoryUpdate();
        return true;
    }
    return false;
}
