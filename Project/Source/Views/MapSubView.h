#pragma once
#include "../DataModels/WorldDataModel.h"
#include "../Domains/World/World.h"
#include <boost/signals2/signal.hpp>

class MapSubView
{
private:
	int id;
	void UpdateSubView(WorldDataModel* worldDataModel);
public:
	MapSubView(int id, std::shared_ptr<World> world);
	boost::signals2::signal<void(int id, std::string output)> onMapSubViewUpdated;
};
