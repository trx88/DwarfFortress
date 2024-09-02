#include "UseCommand.h"
#include "../../Domains/Entities/Player.h"

UseCommand::UseCommand(ItemType itemType)
{
    this->itemType = itemType;
}

bool UseCommand::Execute(std::shared_ptr<World> world, std::shared_ptr<Entity> entity)
{
    auto player = std::static_pointer_cast<Player>(entity);
    switch (itemType)
    {
        case ItemType::Potion:
        {
            return player->UsePotion();
        }break;
        case ItemType::Weapon:
        {
            return player->SwapWeapons();
        }break;
        case ItemType::Armor:
        {
            return player->SwapArmor();
        }break;
    }
}
