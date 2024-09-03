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
        controller->Run();
    }
}

void Game::LoadGame(std::string jsonFile)
{
    world = std::make_shared<World>();
    world->InitializeFromJSON(jsonFile);

    controller = std::make_unique<MainController>(world);
    controller->onReloadGame.connect([this]() { ReloadGame(); });

    auto player = world->GetPlayer();
    mainView = std::make_unique<MainView>(world, player);

    world->SignalWorldUpdate();//To refresh map in the console
    player->SignalPlayerStatsUpdate();//To refresh stats in the console
    player->AccessInventory()->SignalInventoryUpdate();//To refresh inventory in the console
    player->SignalPlayerActionUpdate();//To refresh action in the console
}

void Game::ReloadGame()
{
    LoadGame("Data\\Save.json");
}
