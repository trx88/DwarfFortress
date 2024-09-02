#include "ItemUsageHandler.h"

ItemUsageHandler::ItemUsageHandler()
{
	successor = nullptr;
}

void ItemUsageHandler::SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor)
{
	if (successor == nullptr)
	{
		this->successor = successor;
	}
}

//bool ItemUsageHandler::HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
//{
//}
