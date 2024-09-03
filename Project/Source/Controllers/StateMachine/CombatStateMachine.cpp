#include "CombatStateMachine.h"
#include "../../Domains/World/World.h"
#include "../../Domains/Entities/Player.h"
#include "../../Domains/Entities/Enemy.h"
#include <boost/signals2/signal.hpp>
#include <chrono>
#include <thread>

CombatStateMachine::CombatStateMachine(std::shared_ptr<World> world)
{
	currentState = GameState::Movement;
	this->world = world;
	this->player = world->GetPlayer();
	playerTurns = 0;
	enemyTurns = 0;
}

CombatStateMachine::~CombatStateMachine()
{
}

bool CombatStateMachine::CheckForCombat()
{
	enemies = world->GetEnemiesAtPosition(player->GetRow(), player->GetColumn());
	if (enemies.size() > 0)
	{
		return true;
	}
	return false;
}

void CombatStateMachine::StartCombat()
{
	playerTurns = 0;
	enemyTurns = 0;
	currentEnemy = enemies.front();
	currentState = GameState::PlayerTurn;
}

void CombatStateMachine::Update()
{
	switch (currentState)
	{
		case GameState::Movement:
		{
			if (CheckForCombat())
			{
				player->GameStateCombatMessage();
				currentState = GameState::CombatStart;
			}
			else
			{
				player->GameStateMovementMessage();
			}
		} break;

		case GameState::CombatStart:
		{
			StartCombat();
			currentState = GameState::PlayerTurn;
		} break;

		case GameState::PlayerTurn:
		{
			int damageToApply = player->GetDamage() - currentEnemy->GetArmor();
			int damageToApplyClamped = std::min(std::max(damageToApply, 0), 100);
			currentEnemy->UpdateHealth(currentEnemy->GetHealth() - damageToApplyClamped);
			player->DamageDealtMessage(damageToApplyClamped);
			playerTurns++;

			currentState = GameState::ResolveTurn;
		} break;

		case GameState::EnemyTurn:
		{
			int damageToApply = currentEnemy->GetDamage() - player->GetArmor();
			int damageToApplyClamped = std::min(std::max(damageToApply, 0), 100);
			player->UpdateHealth(player->GetHealth() - damageToApplyClamped);
			player->DamageTakenMessage(damageToApplyClamped);
			enemyTurns++;

			currentState = GameState::ResolveTurn;
		} break;

		case GameState::ResolveTurn:
		{
			if (player->GetHealth() <= 0 || currentEnemy->GetHealth() <= 0)
			{
				currentState = GameState::CombatEnd;
			}
			else
			{
				if (playerTurns > enemyTurns)
				{
					currentState = GameState::EnemyTurn;
				}
				else
				{
					currentState = GameState::PlayerTurn;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		} break;

		case GameState::CombatEnd:
		{
			if (player->GetHealth() > 0)
			{
				auto droppedItems = currentEnemy->DropItems();
				for (const auto& item : droppedItems)
				{
					player->PickUpItem(item);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}

				world->RemoveFromWorld(currentEnemy);
				enemies.erase(std::remove(enemies.begin(), enemies.end(), currentEnemy), enemies.end());
				currentEnemy = nullptr;

				if (enemies.size() > 0)
				{
					currentEnemy = enemies.front();
					currentState = GameState::CombatStart;
				}
				else
				{
					currentState = GameState::Movement;
					player->GameStateMovementMessage();
					player->CombatWonMessage();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			else
			{
				//Update View
				currentState = GameState::Movement;
				player->GameStateMovementMessage();
				player->CombatLostMessage();
				onPlayerDead();
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
		} break;

		default:
			break;
	}
}

bool CombatStateMachine::IsMovementPhase() const
{
	return currentState == GameState::Movement;
}

bool CombatStateMachine::CombatStarted() const
{
	return currentState == GameState::CombatStart;
}
