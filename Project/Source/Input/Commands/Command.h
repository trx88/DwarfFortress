#pragma once
#include "../../Domains/World/World.h"

class CommandKeys
{
public:
    static const char MOVE_UP = 'w';
    static const char MOVE_DOWN = 's';
    static const char MOVE_LEFT = 'a';
    static const char MOVE_RIGHT = 'd';
    static const char INVENTORY_POTION = 'f';
    static const char INVENTORY_WEAPON = 'e';
    static const char INVENTORY_ARMOR = 'r';
    static const char GAME_QUIT = 'q';
    static const char GAME_SAVE = 'p';
    static const char GAME_LOAD = 'l';
};

class Command {
public:
    virtual ~Command();
    virtual bool Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity) = 0;
};

