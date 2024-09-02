#pragma once
#include "ItemUsageHandler.h"
class WeaponHandler : public ItemUsageHandler
{
public:
	WeaponHandler();
	~WeaponHandler();
	void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) override;
	bool HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData) override;
};

