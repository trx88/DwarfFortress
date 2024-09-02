#include "LoadCommand.h"
#include "../../Domains/IO/SaveLoadService.h"
#include "../../Domains/Entities/Player.h"

LoadCommand::LoadCommand()
{
	saveLoadService = std::make_unique<SaveLoadService>();
}

bool LoadCommand::Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
	return saveLoadService->LoadFromJSON(world, std::static_pointer_cast<Player>(entity));
}