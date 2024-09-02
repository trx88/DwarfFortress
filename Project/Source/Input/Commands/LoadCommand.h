#pragma once
#include "Command.h"
class LoadCommand : public Command
{
public:
	LoadCommand();
	bool Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity) override;
};

