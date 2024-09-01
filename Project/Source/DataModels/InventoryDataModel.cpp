#include "InventoryDataModel.h"

InventoryDataModel::InventoryDataModel()
{
}

InventoryDataModel::~InventoryDataModel()
{
}

std::vector<std::shared_ptr<Item>> InventoryDataModel::GetAllItems()
{
	return items;
}

std::vector<std::shared_ptr<Item>> InventoryDataModel::GetItemsByType(ItemType type)
{
	std::vector<std::shared_ptr<Item>> itemsByType;

	for (const auto& item : items)
	{
		if (item->GetType() == type)
		{
			itemsByType.push_back(item);
		}
	}

	return itemsByType;
}

void InventoryDataModel::AddItem(std::shared_ptr<Item> item)
{
	bool alreadyInInventory = false;

	for (const auto& storedItem : items)
	{
		if (storedItem == item)
		{
			storedItem->SetStacks(storedItem->GetStacks() + item->GetStacks());
			alreadyInInventory = true;
			break;
		}
	}

	if (!alreadyInInventory)
	{
		items.push_back(item);
	}
}

void InventoryDataModel::DeleteItem(std::shared_ptr<Item> item)
{
	items.erase(std::remove(items.begin(), items.end(), item), items.end());
}
