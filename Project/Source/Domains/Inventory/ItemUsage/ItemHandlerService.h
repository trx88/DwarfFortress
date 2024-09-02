#pragma once
#include <vector>
#include <memory>
#include "ItemUsageHandler.h"

class ItemHandlerService
{
private:
	std::vector<std::shared_ptr<ItemUsageHandler>> itemHandlers;
public:
	ItemHandlerService();
	void RegisterHandler(std::shared_ptr<ItemUsageHandler> handler);
	bool Handle(std::shared_ptr<Item> item, EntityStatsDataModel* statsData);
};

