#pragma once
#include <string>
#include "../../DataModels/WorldDataModel.h"
#include <nlohmann/json.hpp>

class World
{
private:
	std::unique_ptr<WorldDataModel> worldData;

	//void parseLegend(const nlohmann::json& legend);
	void parseMap(const nlohmann::json& mapData);
	void parseEntities(const nlohmann::json& entitiesData);//player, enemies, obstacles, chests
public:
	World();
	~World();
	bool initializeFromJSON(const std::string& filePath);
};

