#pragma once
#include <memory>
#include "../../DataModels/InventoryDataModel.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>

class Inventory
{
private:
	std::unique_ptr<InventoryDataModel> inventoryData;
public:
	Inventory();
	~Inventory();
	void StoreItem(std::shared_ptr<Item> item);
	void RemoveItem(std::shared_ptr<Item> item);
	bool UseItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData);
	std::vector<std::shared_ptr<Item>> GetItemsByType(ItemType type);

	boost::signals2::signal<void(InventoryDataModel* inventoryDataModel)> onInventoryUpdated;
	void SignalInventoryUpdate();
};

