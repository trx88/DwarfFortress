#include "Player.h"
#include "Chest.h"

Player::Player(int id, EntityType type, int row, int column, int health, int armor, int damage)
	: Entity(id, type, row, column, health, armor, damage)
{
	inventory = std::make_unique<Inventory>();
}

Player::~Player()
{
}

void Player::UpdateHealth(int newHealth)
{
	statsData->SetHealthPoints(newHealth);
	SignalPlayerStatsUpdate();
}

void Player::UpdateArmor(int newArmor)
{
	statsData->SetArmorPoints(newArmor);
	SignalPlayerStatsUpdate();
}

void Player::UpdateDamage(int newDamage)
{
	statsData->SetDamage(newDamage);
	SignalPlayerStatsUpdate();
}

void Player::SignalPlayerStatsUpdate()
{
	onPlayerStatsUpdated(statsData.get());
}

bool Player::UsePotion()
{
	auto potion = inventory->GetItemsByType(ItemType::Potion).front();
	if (potion && inventory->UseItem(potion, statsData.get()))
	{
		inventory->RemoveItem(potion);
		SignalPlayerStatsUpdate();
		return true;
	}

	return false;
}

bool Player::SwapWeapons()
{
	auto weapons = inventory->GetItemsByType(ItemType::Weapon);
	if (weapons.size() > 0)
	{
		std::shared_ptr<Item> weaponToEquip = nullptr;
		//Find equipped item
		for (int i=0; i<weapons.size(); i++)
		{
			if (weapons[i]->IsEquipped())
			{
				//If equipped exists, get next one to equip
				if (weapons.size() > i + 1)
				{
					weapons[i]->SetEquipped(false);
					weaponToEquip = weapons[i + 1];
					break;
				}
				else
				{
					weapons[i]->SetEquipped(false);
					weaponToEquip = weapons[0];
					break;
				}
			}
		}

		//If no weapon is equipped
		if (weaponToEquip == nullptr)
		{
			weaponToEquip = weapons.front();
		}

		if (inventory->UseItem(weaponToEquip, statsData.get()))
		{
			weaponToEquip->SetEquipped(true);
			SignalPlayerStatsUpdate();
			inventory->SignalInventoryUpdate();
			return true;
		}
	}

	return false;
}

bool Player::SwapArmor()
{
	auto armors = inventory->GetItemsByType(ItemType::Armor);
	if (armors.size() > 0)
	{
		std::shared_ptr<Item> armorToEquip = nullptr;
		//Find equipped item
		for (int i = 0; i < armors.size(); i++)
		{
			if (armors[i]->IsEquipped())
			{
				//If equipped exists, get next one to equip
				if (armors.size() > i + 1)
				{
					armors[i]->SetEquipped(false);
					armorToEquip = armors[i + 1];
					break;
				}
				else
				{
					armors[i]->SetEquipped(false);
					armorToEquip = armors[0];
					break;
				}
			}
		}

		//If no armor is equipped
		if (armorToEquip == nullptr)
		{
			armorToEquip = armors.front();
		}

		if (inventory->UseItem(armorToEquip, statsData.get()))
		{
			armorToEquip->SetEquipped(true);
			SignalPlayerStatsUpdate();
			inventory->SignalInventoryUpdate();
			return true;
		}
	}

	return false;
}

void Player::OpenChestAndStoreItems(std::shared_ptr<class Chest> chest)
{
	for (const auto& item : chest->GetChestContents())
	{
		inventory->StoreItem(item);
	}
}
