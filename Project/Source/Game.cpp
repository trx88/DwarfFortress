#include "Game.h"
#include "Domains/World/World.h"
#include "Views/MainView.h"
#include "Domains/Entities/Player.h"
#include "Input/InputManager/InputManager.h"
#include "Controllers/MainController.h"

Game::Game()
{
    world = std::make_shared<World>();
    world->InitializeFromJSON("Data\\World.json");
    
    auto player = world->GetPlayer();
    mainView = std::make_unique<MainView>(world, player);

    world->SignalWorldUpdate();
    player->SignalPlayerStatsUpdate();
    player->AccessInventory()->SignalInventoryUpdate();

    inputManager = std::make_unique<InputManager>(world);
    controller = std::make_unique<MainController>(world, inputManager.get());
}

Game::~Game()
{
}

void Game::Run()
{
    while (true)
    {
        inputManager->ProcessInput();
    }
}
