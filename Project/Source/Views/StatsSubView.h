#pragma once
#include <memory>
#include "../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>

class StatsSubView
{
private:
	int id;
	void UpdateSubView(EntityStatsDataModel* entityStatsDataModel);
public:
	StatsSubView(int id, std::shared_ptr<class Player> player);
	boost::signals2::signal<void(int id, std::string output)> onStatsSubViewUpdated;
};

