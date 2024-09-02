#include "PotionHandler.h"

PotionHandler::PotionHandler() : ItemUsageHandler()
{
}

PotionHandler::~PotionHandler()
{
}

void PotionHandler::SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor)
{
	this->successor = successor;
}

bool PotionHandler::HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	if (item->GetType() == ItemType::Potion)
	{
		statsData->SetHealthPoints(statsData->GetHealthPoints() + item->GetModifier());
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
