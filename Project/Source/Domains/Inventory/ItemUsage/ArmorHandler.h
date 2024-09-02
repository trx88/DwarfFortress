#pragma once
#include "ItemUsageHandler.h"
class ArmorHandler : public ItemUsageHandler
{
public:
	ArmorHandler();
	~ArmorHandler();
	void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) override;
	bool HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData) override;
};

