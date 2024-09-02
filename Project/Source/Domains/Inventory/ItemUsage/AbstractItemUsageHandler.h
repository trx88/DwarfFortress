#pragma once
#include <memory>
#include "../Item.h"
#include "../../../DataModels/EntityStatsDataModel.h"

class AbstractItemUsageHandler
{
public:
	virtual void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) = 0;
	virtual bool HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData) = 0;
};

