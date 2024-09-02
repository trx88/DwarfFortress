#include "ItemHandlerService.h"
#include "PotionHandler.h"
#include "WeaponHandler.h"
#include "ArmorHandler.h"

ItemHandlerService::ItemHandlerService()
{
	RegisterHandler(std::make_shared<PotionHandler>());
	RegisterHandler(std::make_shared<WeaponHandler>());
	RegisterHandler(std::make_shared<ArmorHandler>());
}

void ItemHandlerService::RegisterHandler(std::shared_ptr<ItemUsageHandler> handler)
{
	if (itemHandlers.size() > 0)
	{
		itemHandlers[itemHandlers.size() - 1]->SetSuccessor(handler);
	}

	itemHandlers.push_back(handler);
}

bool ItemHandlerService::Handle(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	return itemHandlers.front()->HandleItem(item, statsData);
}
