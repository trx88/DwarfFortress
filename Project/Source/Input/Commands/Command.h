#pragma once
#include "../../Domains/World/World.h"

class Command {
public:
    virtual ~Command();
    virtual void execute(World& world, std::shared_ptr<Entity> entity) = 0;
};

