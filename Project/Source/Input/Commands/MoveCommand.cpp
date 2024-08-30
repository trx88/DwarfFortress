#include "MoveCommand.h"
#include "../../Domains/Entities/Entity.h"
#include "../../Domains/World/World.h"

MoveCommand::MoveCommand(int deltaColumn, int deltaRow)
{
	this->deltaColumn = deltaColumn;
	this->deltaRow = deltaRow;
}

bool MoveCommand::execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
	int newColumn = entity->GetColumn() + deltaColumn;
	int newRow = entity->GetRow() + deltaRow;

	if (world->IsTileValidForMovement(newRow, newColumn))
	{
		world->MoveEntity(entity, newRow, newColumn);
		return true;
	}

	return false;
}
