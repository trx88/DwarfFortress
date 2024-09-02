#pragma once
#include <memory>
#include "../../DataModels/InventoryDataModel.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>

class Inventory
{
private:
	std::unique_ptr<InventoryDataModel> inventoryData;
	std::unique_ptr<class ItemHandlerService> itemHandlerService;
public:
	Inventory();
	~Inventory();
	void StoreItem(std::shared_ptr<Item> item);
	void RemoveItem(std::shared_ptr<Item> item);
	bool UseItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData);
	std::vector<std::shared_ptr<Item>> GetItemsByType(ItemType type);
	std::vector<std::shared_ptr<Item>> GetItems();

	boost::signals2::signal<void(InventoryDataModel* inventoryDataModel)> onInventoryUpdated;
	void SignalInventoryUpdate();
};

