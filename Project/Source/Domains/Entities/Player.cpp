#include "Player.h"
#include "Chest.h"
#include "../../DataModels/PlayerActionsDataModel.h"

Player::Player(int id, EntityType type, int row, int column, int health, int armor, int damage)
	: Entity(id, type, row, column, health, armor, damage)
{
	inventory = std::make_unique<Inventory>();
	playerActions = std::make_unique<PlayerActionsDataModel>();
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

void Player::SignalPlayerActionUpdate()
{
	onPlayerActionMessageUpdated(playerActions.get());
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
					//Cycle to first, if last one is equipped
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
					//Cycle to first, if last one is equipped
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

void Player::PickUpItem(std::shared_ptr<Item> item)
{
	inventory->StoreItem(item);
	playerActions->ItemPickedUp(item);
	SignalPlayerActionUpdate();
}

void Player::OpenChestAndStoreItems(std::shared_ptr<class Chest> chest)
{
	for (const auto& item : chest->GetChestContents())
	{
		PickUpItem(item);
	}
}

void Player::GameStateMovementMessage()
{
	playerActions->GameStateMovement();
	SignalPlayerActionUpdate();
}

void Player::GameStateCombatMessage()
{
	playerActions->GameStateCombat();
	SignalPlayerActionUpdate();
}

void Player::DamageDealtMessage(int damage)
{
	playerActions->DamageDealt(damage);
	SignalPlayerActionUpdate();
}

void Player::DamageTakenMessage(int damage)
{
	playerActions->DamageTaken(damage);
	SignalPlayerActionUpdate();
}

void Player::CombatWonMessage()
{
	playerActions->CombatWon();
	SignalPlayerActionUpdate();
}

void Player::CombatLostMessage()
{
	playerActions->CombatLost();
	SignalPlayerActionUpdate();
}

void Player::EmptyActionMessage()
{
	playerActions->EmptyAction();
	SignalPlayerActionUpdate();
}

nlohmann::json Player::PlayerToJSON()
{
	nlohmann::json jsonData;

	nlohmann::json jsonPlayerObject = nlohmann::json::object();
	jsonPlayerObject["type"] = static_cast<int>(GetType());
	jsonPlayerObject["column"] = static_cast<int>(GetColumn());
	jsonPlayerObject["row"] = static_cast<int>(GetRow());
	
	nlohmann::json jsonStatsObject = nlohmann::json::object();
	jsonStatsObject["health"] = static_cast<int>(statsData->GetHealthPoints());
	jsonStatsObject["armor"] = static_cast<int>(statsData->GetArmorPoints());
	jsonStatsObject["damage"] = static_cast<int>(statsData->GetDamage());
	jsonPlayerObject["stats"] = jsonStatsObject;

	nlohmann::json jsonInventoryObject = nlohmann::json::array();
	for (const auto& item : inventory->GetItems())
	{
		nlohmann::json jsonItemObject = nlohmann::json::object();
		jsonItemObject["name"] = item->GetName();
		jsonItemObject["type"] = static_cast<int>(item->GetType());
		jsonItemObject["modifier"] = item->GetModifier();
		jsonItemObject["stacks"] = item->GetStacks();

		jsonInventoryObject.push_back(jsonItemObject);
	}

	jsonPlayerObject["inventory"] = jsonInventoryObject;

	return jsonData["player"] = jsonPlayerObject;
}
