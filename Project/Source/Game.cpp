#include "Game.h"

Game::Game()
{
    world = std::make_shared<World>();
    view = std::make_shared<MapSubView>(world);
    world->initializeFromJSON("Data\\World.json");
}

void Game::Run()
{
    while (true)
    {
        //view->Render();
    }
}
