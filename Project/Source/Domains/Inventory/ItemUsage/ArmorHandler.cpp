#include "ArmorHandler.h"

ArmorHandler::ArmorHandler()
{
}

ArmorHandler::~ArmorHandler()
{
}

void ArmorHandler::SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor)
{
	this->successor = successor;
}

bool ArmorHandler::HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	if (item->GetType() == ItemType::Armor)
	{
		statsData->SetArmorPoints(item->GetModifier());
		return true;
	}
	else
	{
		if (successor != nullptr)
		{
			return successor->HandleItem(item, statsData);
		}
	}

	return false;
}