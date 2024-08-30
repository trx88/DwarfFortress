#pragma once
#include <memory>

class World;
class Player;

class InputManager
{
private:
	std::shared_ptr<World> world;
	std::shared_ptr<Player> player;
public:
	InputManager(std::shared_ptr<World> world, std::shared_ptr<Player> player);
	~InputManager();
	void ProcessInput();
};

