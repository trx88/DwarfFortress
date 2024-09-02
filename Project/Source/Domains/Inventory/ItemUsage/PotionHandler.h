#pragma once
#include "ItemUsageHandler.h"
class PotionHandler : public ItemUsageHandler
{
public:
	PotionHandler();
	~PotionHandler();
	void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) override;
	bool HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData) override;
};

