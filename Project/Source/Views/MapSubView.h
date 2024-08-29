#pragma once
#include "../DataModels/WorldDataModel.h"
#include "../Domains/World/World.h"

class MapSubView
{
private:
	void UpdateView(WorldDataModel* worldDataModel);
public:
	MapSubView(std::shared_ptr<World> world);
	void Render(std::stringstream& output);
};
