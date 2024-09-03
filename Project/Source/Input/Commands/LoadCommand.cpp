#include "LoadCommand.h"
#include "../../Domains/IO/SaveLoadService.h"
#include "../../Domains/Entities/Player.h"
#include <fstream>
#include <iostream>

LoadCommand::LoadCommand()
{
}

bool LoadCommand::Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
	//return saveLoadService->LoadFromJSON(world, std::static_pointer_cast<Player>(entity));

	//HACK
	//If file exists, will return true, just to get the mechanism going.
	//After this successful command, InputManager will send a message to Game class that can use 
	//initialization code for restarting the game, just from another JSON.
	bool fileExists = true;
	std::ifstream file("Data\\Save.json");
	if (!file.good())
	{
		fileExists = false;
	}
	file.close();

	return fileExists;
}