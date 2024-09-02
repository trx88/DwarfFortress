#pragma once
#include "Command.h"
#include "../../Domains/Inventory/Item.h"

class UseCommand : public Command
{
private:
	ItemType itemType;
public:
	UseCommand(ItemType itemType);
	bool Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity) override;
};

