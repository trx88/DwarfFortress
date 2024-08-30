#include "MainController.h"
#include "../Input/InputManager/InputManager.h"

MainController::MainController(std::shared_ptr<World> world, InputManager* inputManager)
{
	inputManager->onPlayerTurnEnded.connect([this](std::shared_ptr<Player> player) { PlayerMoved(player); });
}

MainController::~MainController()
{
}

void MainController::GameLoop()
{
	
}

void MainController::PlayerMoved(std::shared_ptr<Player> player)
{
	//TODO: Execute enemy turn
	int x = 0;
}
