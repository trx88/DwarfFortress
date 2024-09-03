#pragma once
#include <string>
#include <memory>

class PlayerActionsDataModel
{
private:
	std::string gameState;
	std::string gameAction;
public:
	PlayerActionsDataModel();
	~PlayerActionsDataModel();
	std::string GetGameState() const;
	std::string GetGameAction() const;

	void GameStateMovement();
	void GameStateCombat();
	void DamageDealt(int damage);
	void DamageTaken(int damage);
	void CombatWon();
	void CombatLost();
	void EmptyAction();
	void ItemPickedUp(std::shared_ptr<class Item> item);
};

