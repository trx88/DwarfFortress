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
	nlohmann::json MapToJSON();
	bool InitializeFromJSON(const std::string& filePath);
	bool IsTileValidForMovement(int row, int column) const;
	bool MoveEntity(std::shared_ptr<Entity> entity, int newRow, int newColumn);
	std::shared_ptr<class Player> GetPlayer();
	std::vector<std::shared_ptr<class Enemy>> GetEnemies();
	std::vector<std::shared_ptr<class Chest>> GetChests();
	std::vector<std::shared_ptr<class Entity>> GetObstacles();
	
	boost::signals2::signal<void(WorldDataModel* worldDataModel)> onWorldDataUpdated;
	void SignalWorldUpdate();
};
