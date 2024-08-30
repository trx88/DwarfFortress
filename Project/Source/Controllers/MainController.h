#pragma once
#include <memory>

class InputManager;
class World;
class Player;
class InputManager;

class MainController
{
public:
	MainController(std::shared_ptr<World> world, InputManager* inputManager);
	~MainController();
	//TODO: Maybe move to private?
	void PlayerMoved(std::shared_ptr<Player> player);
};

