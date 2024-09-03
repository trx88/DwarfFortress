#pragma once
#include "Entity.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>
#include <nlohmann/json.hpp>
#include "../Inventory/Inventory.h"

class Player : public Entity
{
private:
	std::unique_ptr<Inventory> inventory;
public:
	Player(int id, EntityType type, int row, int column, int health, int armor, int damage);
	~Player();
	Inventory* AccessInventory() { return inventory.get(); }
	void UpdateHealth(int newHealth) override;
	void UpdateArmor(int newArmor) override;
	void UpdateDamage(int newDamage) override;

	boost::signals2::signal<void(EntityStatsDataModel* entityStatsDataModel)> onPlayerStatsUpdated;
	void SignalPlayerStatsUpdate();

	bool UsePotion();
	bool SwapWeapons();
	bool SwapArmor();
	void OpenChestAndStoreItems(std::shared_ptr<class Chest> chest);

	nlohmann::json PlayerToJSON();
};

