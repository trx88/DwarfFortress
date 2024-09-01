#include "MainController.h"
#include "../Input/InputManager/InputManager.h"
#include "../Domains/World/World.h"
#include "../Domains/Entities/Player.h"
#include "../Domains/Entities/Enemy.h"
#include "../Input/Commands/MoveCommand.h"

MainController::MainController(std::shared_ptr<World> world, InputManager* inputManager)
{
	this->world = world;
	inputManager->onPlayerTurnEnded.connect([this](std::shared_ptr<Player> player) { OnPlayerMoved(player); });
}

MainController::~MainController()
{
}

void MainController::OnPlayerMoved(std::shared_ptr<Player> player)
{
	MoveEnemies(player);
}

void MainController::MoveEnemies(std::shared_ptr<Player> player)
{
	auto enemies = world->GetEnemies();
	for (const auto& enemy : enemies)
	{
		int deltaColumn = player->GetColumn() - enemy->GetColumn();
		int deltaRow = player->GetRow() - enemy->GetRow();

		Command* command = nullptr;

		if (std::abs(deltaColumn) > std::abs(deltaRow))
		{
			//Move horizontally
			if (deltaColumn < 0)
			{
				//Move left
				if (world->IsTileValidForMovement(enemy->GetRow(), enemy->GetColumn() - 1))
				{
					command = new MoveCommand(-1, 0);
				}
			}
			else
			{
				//Move right
				if (world->IsTileValidForMovement(enemy->GetRow(), enemy->GetColumn() + 1))
				{
					command = new MoveCommand(1, 0);
				}
			}
		}
		else
		{
			//Move vertically
			if (deltaRow < 0)
			{
				//Move up
				if (world->IsTileValidForMovement(enemy->GetRow() - 1, enemy->GetColumn()))
				{
					command = new MoveCommand(0, -1);
				}
			}
			else
			{
				//Move down
				if (world->IsTileValidForMovement(enemy->GetRow() + 1, enemy->GetColumn()))
				{
					command = new MoveCommand(0, 1);
				}
			}
		}

		//If direct path is blocked
		/*if (player->GetColumn() != enemy->GetColumn() && player->GetRow() != enemy->GetRow())
		{
			if (deltaColumn < 0 && world->IsTileValidForMovement(enemy->GetRow(), enemy->GetColumn() - 1))
			{
				command = new MoveCommand(-1, 0);
			}
			else if (deltaColumn > 0 && world->IsTileValidForMovement(enemy->GetRow(), enemy->GetColumn() + 1))
			{
				command = new MoveCommand(1, 0);
			}
			else if (deltaRow < 0 && world->IsTileValidForMovement(enemy->GetRow() - 1, enemy->GetColumn()))
			{
				command = new MoveCommand(0, -1);
			}
			else if (deltaRow > 0 && world->IsTileValidForMovement(enemy->GetRow() + 1, enemy->GetColumn()))
			{
				command = new MoveCommand(0, 1);
			}
		}*/

		if (command)
		{
			command->Execute(world, enemy);
		}
		delete command;
	}
}
