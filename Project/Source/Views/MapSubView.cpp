#include "MapSubView.h"
#include <sstream>
#include "../Domains/Entities/Entity.h"
#include <iostream>

MapSubView::MapSubView(std::shared_ptr<World> world)
{
	world->onWorldDataUpdated.connect([this](WorldDataModel* worldDataMode) {UpdateView(worldDataMode); });
}

void MapSubView::UpdateView(WorldDataModel* worldDataModel)
{
    std::stringstream output;
    output << "\033[H"; // Move cursor to top-left to avoid flickering

    //TODO: UI MOCKUP. SPLIT INTO SUBVIES
    output << "---LEGEND--" << "\n";
    output << "Player: P Enemy: E Chest: C Mountain: M Tree: T" << "\n";
    output << "Move: WASD Potion: F Confirm/Cancel: Y/N Save: P Load: L Quit: Q" << "\n";
    output << "\n";

    output << "----MAP----" << "\n";
    
    // Render the entire world, including entities
    for (int row = 0; row < worldDataModel->GetHeight(); ++row) {
        for (int column = 0; column < worldDataModel->GetWidth(); ++column) {
            // Check if there's an entity at this position
            auto entity = worldDataModel->GetEntityAt(row, column);
            if (entity) 
            {
                output << entity->GetTileSymbol();  // Render the entity's symbol
            }
            else 
            {
                // Otherwise, render the map tile
                output << worldDataModel->GetTileAt(row, column);
            }
        }
        output << "\n"; // Newline after each row
    }
    output << "\n";

    output << "---STATS---" << "\n";
    output << "HP: 10" << "\n";
    output << "AP: 2" << "\n";
    output << "DMG: 3" << "\n";
    output << "\n";
    output << "-INVENTORY-" << "\n";
    output << "POTION: 1" << "\n";
    output << "SWORD" << "\n";
    output << "SCALE MAIL" << "\n";
    output << "\n";
    output << "--ACTIONS--" << "\n";
    output << "You picked up a chest containing 1 POTION" << "\n";

    Render(output);
}

void MapSubView::Render(std::stringstream& output)
{
    std::cout << output.str();
}
