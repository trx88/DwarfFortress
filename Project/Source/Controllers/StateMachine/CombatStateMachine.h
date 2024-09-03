#pragma once
#include <memory>
#include <vector>
#include <boost/signals2/signal.hpp>

enum class GameState {
    Movement = 0,
    CombatStart = 1,
    PlayerTurn = 2,
    EnemyTurn = 3,
    ResolveTurn = 4,
    CombatEnd = 5
};

class CombatStateMachine
{
private:
    GameState currentState;
    std::shared_ptr<class World> world;
    std::shared_ptr<class Player> player;
    std::shared_ptr<class Enemy> currentEnemy;
    std::vector<std::shared_ptr<class Enemy>> enemies;
    int playerTurns, enemyTurns;

    bool CheckForCombat();
    void StartCombat();
public:
    CombatStateMachine(std::shared_ptr<World> world);
    ~CombatStateMachine();
    void Update();
    bool IsMovementPhase() const;
    bool CombatStarted() const;

    boost::signals2::signal<void()> onPlayerDead;
};

