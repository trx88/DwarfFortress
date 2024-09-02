#include "SaveCommand.h"
#include "../../Domains/IO/SaveLoadService.h"
#include "../../Domains/Entities/Player.h"

SaveCommand::SaveCommand()
{
	saveLoadService = std::make_unique<SaveLoadService>();
}

bool SaveCommand::Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
	return saveLoadService->SaveToJSON(world, std::static_pointer_cast<Player>(entity));
}
