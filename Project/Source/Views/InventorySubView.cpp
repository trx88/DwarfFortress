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
    std::string equippedText = " Equipped";
    //HACK: Adding spaces to avoid clearing the console since it flickers.
    std::string equippedTest = "         ";

    output += "\x1B[92m-INVENTORY-\n";
    output += "\x1B[37m"; //Print in white
    auto inventoryItems = inventoryDataModel->GetAllItems();
    for (const auto& item : inventoryItems)
    {
        output += item->GetName();
        output += ": ";
        output += std::to_string(item->GetStacks());
        if (item->IsEquipped())
        {
            output += " Equipped";
        }
        else
        {
            output += equippedTest;
        }
        output += "\n";
    }
    output += "\n";
    
    onInventorySubViewUpdated(id, output);
}
