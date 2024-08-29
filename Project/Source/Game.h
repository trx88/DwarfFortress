#pragma once
#include <memory>
#include "Domains/World/World.h"
#include "Views/MapSubView.h"
#include "Domains/Entities/Player.h"

class Game {
public:
    Game();
    void Run();

private:
    std::shared_ptr<World> world;
    std::shared_ptr<Player> player;
    std::shared_ptr<MapSubView> view;
};
