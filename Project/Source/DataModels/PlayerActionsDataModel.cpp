#include "PlayerActionsDataModel.h"
#include "../Domains/Inventory/Item.h"

PlayerActionsDataModel::PlayerActionsDataModel()
{
	gameState = "\x1B[36mMOVEMENT PHASE";
	gameAction = "";
}

PlayerActionsDataModel::~PlayerActionsDataModel()
{
}

std::string PlayerActionsDataModel::GetGameState() const
{
	return gameState;
}

std::string PlayerActionsDataModel::GetGameAction() const
{
	return gameAction;
}

void PlayerActionsDataModel::GameStateMovement()
{
	gameState = "\x1B[36mMOVEMENT PHASE";
}

void PlayerActionsDataModel::GameStateCombat()
{
	gameState = "\x1B[31mCOMBAT PHASE";
}

void PlayerActionsDataModel::DamageDealt(int damage)
{
	gameAction = "\x1B[37mYou dealt " + std::to_string(damage) + " damage";
}

void PlayerActionsDataModel::DamageTaken(int damage)
{
	gameAction = "\x1B[37mYou took " + std::to_string(damage) + " damage";
}

void PlayerActionsDataModel::CombatWon()
{
	gameAction = "\x1B[37mYou're victorious!";
}

void PlayerActionsDataModel::CombatLost()
{
	gameAction = "\x1B[37mYOU DIED!";
}

void PlayerActionsDataModel::EmptyAction()
{
	gameAction = "                                                                  ";
}

void PlayerActionsDataModel::ItemPickedUp(std::shared_ptr<class Item> item)
{
	gameAction = "\x1B[37mYou picked up " + std::to_string(item->GetStacks()) + " " + item->GetName();
}
