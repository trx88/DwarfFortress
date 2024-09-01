#include "Inventory.h"

Inventory::Inventory()
{
	inventoryData = std::make_unique<InventoryDataModel>();
}

Inventory::~Inventory()
{
	
}

void Inventory::StoreItem(std::shared_ptr<Item> item)
{
	inventoryData->AddItem(item);
	SignalInventoryUpdate();
}

void Inventory::RemoveItem(std::shared_ptr<Item> item)
{
	inventoryData->DeleteItem(item);
	SignalInventoryUpdate();
}

bool Inventory::UseItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	//TODO: Write a chain of reponsibility for consuming/equiping items.
	return true;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItemsByType(ItemType type)
{
	return inventoryData->GetItemsByType(type);
}

void Inventory::SignalInventoryUpdate()
{
	onInventoryUpdated(inventoryData.get());
}
