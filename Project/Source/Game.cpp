#include "Game.h"
#include "Domains/World/World.h"
#include "Views/MapSubView.h"
#include "Domains/Entities/Player.h"
#include "Input/InputManager/InputManager.h"
#include "Controllers/MainController.h"

Game::Game()
{
    world = std::make_shared<World>();
    view = std::make_shared<MapSubView>(world);
    world->initializeFromJSON("Data\\World.json");
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
