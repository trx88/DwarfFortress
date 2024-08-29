#include "World.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

World::World()
{
	model = std::make_unique<WorldDataModel>();
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

    model->SetMapSize(jsonData["width"], jsonData["height"]);

    return true;
}
