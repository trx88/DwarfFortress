#pragma once
#include <memory>
#include <boost/signals2/signal.hpp>

class InputManager;
class World;
class Player;
class InputManager;
class CombatStateMachine;

class MainController
{
private:
	std::shared_ptr<World> world;
	std::unique_ptr<InputManager> inputManager;
	std::unique_ptr<CombatStateMachine> combatStateMachine;
public:
	MainController(std::shared_ptr<World> world);
	~MainController();
	void Run();
	void OnReloadGame();
	void OnPlayerDead();
	void OnPlayerMoved(std::shared_ptr<Player> player);
	void MoveEnemies(std::shared_ptr<Player> player);

	boost::signals2::signal<void()> onReloadGame;
};
