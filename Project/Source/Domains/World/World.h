#pragma once
#include <string>
#include "../../DataModels/WorldDataModel.h"

//class WorldDataModel;

class World
{
private:
	std::unique_ptr<WorldDataModel> model;
public:
	World();
	~World();
	bool initializeFromJSON(const std::string& filePath);
};

