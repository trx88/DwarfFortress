#pragma once
#include <memory>
#include "../DataModels/InventoryDataModel.h"
#include <boost/signals2/signal.hpp>

class InventorySubView
{
private:
	int id;
	void UpdateSubView(InventoryDataModel* inventoryDataModel);
public:
	InventorySubView(int id, std::shared_ptr<class Player> player);
	boost::signals2::signal<void(int id, std::string output)> onInventorySubViewUpdated;
};

