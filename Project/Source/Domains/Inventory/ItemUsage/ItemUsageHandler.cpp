#include "ItemUsageHandler.h"

ItemUsageHandler::ItemUsageHandler()
{
	successor = nullptr;
}

ItemUsageHandler::~ItemUsageHandler()
{
}

void ItemUsageHandler::SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor)
{
	if (successor == nullptr)
	{
		this->successor = successor;
	}
}
