#pragma once
#include <memory>

class InputManager;
class World;
class Player;
class InputManager;

class MainController
{
private:
	//InputManager
public:
	MainController(std::shared_ptr<World> world, InputManager* inputManager);
	~MainController();
	void GameLoop();
	void PlayerMoved(std::shared_ptr<Player> player);
};

