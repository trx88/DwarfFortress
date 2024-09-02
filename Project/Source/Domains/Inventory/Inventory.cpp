#include "Inventory.h"
#include "ItemUsage/ItemHandlerService.h"

Inventory::Inventory()
{
	inventoryData = std::make_unique<InventoryDataModel>();
	itemHandlerService = std::make_unique<ItemHandlerService>();
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
	if (item->GetStacks() == 1)
	{
		inventoryData->DeleteItem(item);
	}
	else
	{
		item->SetStacks(item->GetStacks() - 1);
	}
	SignalInventoryUpdate();
}

bool Inventory::UseItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	if (itemHandlerService->Handle(item, statsData))
	{

		return true;
	}
	return false;
}

std::vector<std::shared_ptr<Item>> Inventory::GetItemsByType(ItemType type)
{
	return inventoryData->GetItemsByType(type);
}

void Inventory::SignalInventoryUpdate()
{
	onInventoryUpdated(inventoryData.get());
}
