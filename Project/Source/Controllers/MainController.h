#pragma once
#include <memory>

class InputManager;
class World;
class Player;
class InputManager;

class MainController
{
private:
	std::shared_ptr<World> world;
public:
	MainController(std::shared_ptr<World> world, InputManager* inputManager);
	~MainController();
	//TODO: Maybe move to private?
	void OnPlayerMoved(std::shared_ptr<Player> player);
	void MoveEnemies(std::shared_ptr<Player> player);
};

