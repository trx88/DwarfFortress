#pragma once
#include "Command.h"

class MoveCommand : public Command
{
private:
	int deltaColumn, deltaRow = 0;
public:
	MoveCommand(int deltaColumn, int deltaRow);
	void execute(World& world, std::shared_ptr<Entity> entity) override;
};

