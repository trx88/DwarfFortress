#pragma once
#include <string>
#include "../../DataModels/WorldDataModel.h"
#include <nlohmann/json.hpp>
#include <boost/signals2/signal.hpp>

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
	bool isTileOccupied(int row, int column) const;
	bool MoveEntity(std::shared_ptr<Entity> entity, int newRow, int newColumn);
	
	//TODO: Should probably move this to the Controller
	boost::signals2::signal<void(WorldDataModel* worldDataModel)> worldDataUpdated;
};

