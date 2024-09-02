#include "Game.h"
#include "Domains/World/World.h"
#include "Views/MainView.h"
#include "Domains/Entities/Player.h"
#include "Input/InputManager/InputManager.h"
#include "Controllers/MainController.h"

Game::Game()
{
    LoadGame("Data\\World.json");
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

void Game::LoadGame(std::string jsonFile)
{
    world = std::make_shared<World>();
    world->InitializeFromJSON(jsonFile);

    auto player = world->GetPlayer();
    mainView = std::make_unique<MainView>(world, player);

    world->SignalWorldUpdate();
    player->SignalPlayerStatsUpdate();
    player->AccessInventory()->SignalInventoryUpdate();

    inputManager = std::make_unique<InputManager>(world);
    controller = std::make_unique<MainController>(world, inputManager.get());
    inputManager->onReloadGame.connect([this]() { ReloadGame(); });
}

void Game::ReloadGame()
{
    LoadGame("save.json");
}
