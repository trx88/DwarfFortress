#pragma once
#include "AbstractItemUsageHandler.h"

class ItemUsageHandler : public AbstractItemUsageHandler
{
protected:
	std::shared_ptr<AbstractItemUsageHandler> successor;
public:
	ItemUsageHandler();
	void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) override;
	//bool HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData) override;
};

