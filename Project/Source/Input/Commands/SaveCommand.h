#pragma once
#include "Command.h"
class SaveCommand : public Command
{
private:
	std::unique_ptr<class SaveLoadService> saveLoadService;
public:
	SaveCommand();
	bool Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity) override;
};

