#pragma once
#include "Entity.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>
#include "../Inventory/Inventory.h"

class Player : public Entity
{
private:
	std::unique_ptr<Inventory> inventory;
public:
	Player(int id, EntityType type, int row, int column, int health, int armor, int damage);
	~Player();
	Inventory* AccessInventory() { return inventory.get(); }
	void UpdateHealth(int newHealth);
	void UpdateArmor(int newArmor);
	void UpdateDamage(int newDamage);

	boost::signals2::signal<void(EntityStatsDataModel* entityStatsDataModel)> onPlayerStatsUpdated;
	void SignalPlayerStatsUpdate();
	/*boost::signals2::signal<void(InventoryDataModel* inventoryDataModel)> onInventoryUpdated;
	void SignalInventoryUpdate();*/

	bool UsePotion();
};

