#pragma once
#include <vector>
#include <memory>
#include "../Domains/Inventory/Item.h"

class InventoryDataModel
{
private:
	std::vector<std::shared_ptr<Item>> items;
public:
	InventoryDataModel();
	~InventoryDataModel();
	std::vector<std::shared_ptr<Item>> GetAllItems();
	std::vector<std::shared_ptr<Item>> GetItemsByType(ItemType type);
	void AddItem(std::shared_ptr<Item> item);
	void DeleteItem(std::shared_ptr<Item> item);
};
