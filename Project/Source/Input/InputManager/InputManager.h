#pragma once
#include <memory>
#include <boost/signals2/signal.hpp>

class World;
class Player;

class InputManager
{
private:
	std::shared_ptr<World> world;
	std::shared_ptr<Player> player;
public:
	InputManager(std::shared_ptr<World> world);
	~InputManager();
	void ProcessInput();

	boost::signals2::signal<void(std::shared_ptr<Player>)> onPlayerTurnEnded;
};

