#include "Player.h"

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
	auto potion = inventory->GetItemsByType(ItemType::Potion).back();
	if (potion && inventory->UseItem(potion, statsData.get()))
	{
		SignalPlayerStatsUpdate();
		return true;
	}

	return false;
}
