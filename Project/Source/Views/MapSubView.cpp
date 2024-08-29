#include "MapSubView.h"
#include <sstream>
#include "../Domains/Entities/Entity.h"
#include <iostream>

MapSubView::MapSubView(std::shared_ptr<World> world)
{
	world->worldDataUpdated.connect([this](WorldDataModel* worldDataMode) {UpdateView(worldDataMode); });
}

void MapSubView::UpdateView(WorldDataModel* worldDataModel)
{
    std::stringstream output;
    output << "\033[H"; // Move cursor to top-left to avoid flickering

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

    Render(output);
}

void MapSubView::Render(std::stringstream& output)
{
    std::cout << output.str();
}
