#include "UseCommand.h"
#include "../../Domains/Entities/Player.h"

UseCommand::UseCommand()
{
}

bool UseCommand::Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
    auto player = std::static_pointer_cast<Player>(entity);
    return player->UsePotion();
}
