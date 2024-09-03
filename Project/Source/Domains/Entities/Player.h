#pragma once
#include "Entity.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include "../../DataModels/PlayerActionsDataModel.h"
#include <boost/signals2/signal.hpp>
#include <nlohmann/json.hpp>
#include "../Inventory/Inventory.h"

class Player : public Entity
{
private:
	std::unique_ptr<Inventory> inventory;
	std::unique_ptr<class PlayerActionsDataModel> playerActions;
public:
	Player(int id, EntityType type, int row, int column, int health, int armor, int damage);
	~Player();
	Inventory* AccessInventory() { return inventory.get(); }

#pragma region Setters
	void UpdateHealth(int newHealth) override;
	void UpdateArmor(int newArmor) override;
	void UpdateDamage(int newDamage) override;
#pragma endregion

#pragma region Signals
	boost::signals2::signal<void(EntityStatsDataModel* entityStatsDataModel)> onPlayerStatsUpdated;
	void SignalPlayerStatsUpdate();
	boost::signals2::signal<void(PlayerActionsDataModel* playerActionsDataModel)> onPlayerActionMessageUpdated;
	void SignalPlayerActionUpdate();
#pragma endregion

#pragma region Used in command
	bool UsePotion();
	bool SwapWeapons();
	bool SwapArmor();
	void PickUpItem(std::shared_ptr<class Item> item);
	void OpenChestAndStoreItems(std::shared_ptr<class Chest> chest);
#pragma endregion

#pragma region Action messages
	void GameStateMovementMessage();
	void GameStateCombatMessage();
	void DamageDealtMessage(int damage);
	void DamageTakenMessage(int damage);
	void CombatWonMessage();
	void CombatLostMessage();
	void EmptyActionMessage();
#pragma endregion

	nlohmann::json PlayerToJSON();
};

