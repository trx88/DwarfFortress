#pragma once
#include <memory>
#include "../DataModels/PlayerActionsDataModel.h"
#include <boost/signals2/signal.hpp>

class ActionsSubView
{
private:
	int id;
	void UpdateSubView(PlayerActionsDataModel* playerActionsDataModel);
public:
	ActionsSubView(int id, std::shared_ptr<class Player> player);
	boost::signals2::signal<void(int id, std::string output)> onActionsSubViewUpdated;
};

