#pragma once
#include <memory>

class World;
class Player;
class MapSubView;
class StatsSubView;
class MainView;
class InputManager;
class MainController;

class Game {
public:
    Game();
    ~Game();
    void Run();

private:
    std::shared_ptr<World> world;
    std::unique_ptr<MainView> mainView;
    std::unique_ptr<MainController> controller;
    std::unique_ptr<InputManager> inputManager;
};
