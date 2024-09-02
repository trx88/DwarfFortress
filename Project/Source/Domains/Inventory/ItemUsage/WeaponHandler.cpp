#include "WeaponHandler.h"

WeaponHandler::WeaponHandler()
{
}

WeaponHandler::~WeaponHandler()
{
}

void WeaponHandler::SetSuccessor(std::shared_ptr<AbstractItemUsageHandler> successor)
{
	this->successor = successor;
}

bool WeaponHandler::HandleItem(std::shared_ptr<Item> item, EntityStatsDataModel* statsData)
{
	if (item->GetType() == ItemType::Weapon)
	{
		statsData->SetDamage(item->GetModifier());
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
