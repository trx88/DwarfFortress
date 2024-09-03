#pragma once
#include "AbstractItemUsageHandler.h"

class ItemUsageHandler : public AbstractItemUsageHandler
{
protected:
	std::shared_ptr<AbstractItemUsageHandler> successor;
public:
	ItemUsageHandler();
	virtual ~ItemUsageHandler();
	void SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor) override;
};

