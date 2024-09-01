#pragma once
#include "Command.h"

class UseCommand : public Command
{
public:
	UseCommand();
	bool Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity) override;
};

