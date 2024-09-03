#pragma once
#include <memory>

class InputManager;
class World;
class Player;
class InputManager;
class CombatStateMachine;

class MainController
{
private:
	std::shared_ptr<World> world;
	InputManager* inputManager;
	std::unique_ptr<CombatStateMachine> combatStateMachine;
public:
	MainController(std::shared_ptr<World> world, InputManager* inputManager);
	~MainController();
	void Run();
	void OnPlayerDead();
	void OnPlayerMoved(std::shared_ptr<Player> player);
	void MoveEnemies(std::shared_ptr<Player> player);
};
