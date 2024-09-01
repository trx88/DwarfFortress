#include "InventorySubView.h"
#include "../Domains/Entities/Player.h"

InventorySubView::InventorySubView(int id, std::shared_ptr<class Player> player)
{
	this->id = id;
	player->AccessInventory()->onInventoryUpdated.connect([this](InventoryDataModel* inventoryDataModel) {UpdateSubView(inventoryDataModel); });
}

void InventorySubView::UpdateSubView(InventoryDataModel* inventoryDataModel)
{
    std::string output;

    output += "---INVENTORY---\n";
    auto inventoryItems = inventoryDataModel->GetAllItems();
    for (const auto& item : inventoryItems)
    {
        output += item->GetName();
        output += ": ";
        output += std::to_string(item->GetStacks());
        output += "\n";
    }
    output += "\n";

    /*output += "HP: ";
    output += std::to_string(entityStatsDataModel->GetHealthPoints());
    output += "\n";
    output += "AP: ";
    output += std::to_string(entityStatsDataModel->GetArmorPoints());
    output += "\n";
    output += "DMG: ";
    output += std::to_string(entityStatsDataModel->GetDamage());
    output += "\n";*/

    onInventorySubViewUpdated(id, output);
}
