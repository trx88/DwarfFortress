#include "MapSubView.h"
#include "../Domains/Entities/Entity.h"
#include <string>

MapSubView::MapSubView(int id, std::shared_ptr<World> world)
{
    this->id = id;
    world->onWorldDataUpdated.connect([this](WorldDataModel* worldDataMode) {UpdateSubView(worldDataMode); });
}

void MapSubView::UpdateSubView(WorldDataModel* worldDataModel)
{
    std::string output;
    output += "\033[H"; //Move cursor to top-left to avoid flickering

    output += "\x1B[33m---LEGEND--\n";
    output += "\x1B[37mPlayer:\x1B[36mP \x1B[37mEnemy:\x1B[31mE \x1B[37mChest:\x1B[35mC \x1B[37mMountain:\x1B[37mM \x1B[37mTree:\x1B[32mT\n";
    output += "\x1B[92m--CONTROLS-\n";
    output += "\x1B[37mMove:\x1B[92mWASD \x1B[37mPotion:\x1B[92mF \x1B[37mSwap weapon:\x1B[92mE \x1B[37mSwap armor:\x1B[92mR \x1B[37mSave:\x1B[92mP \x1B[37mLoad:\x1B[92mL \x1B[37mQuit:\x1B[92mQ\n";
    output += "\n";

    output += "----MAP----\n";

    //Render the entire world, including entities
    for (int row = 0; row < worldDataModel->GetHeight(); ++row) {
        for (int column = 0; column < worldDataModel->GetWidth(); ++column) {
            //Check if there's an entity at this position
            auto entity = worldDataModel->GetEntityAt(row, column);
            if (entity)
            {
                output += entity->GetTileSymbolForPrint();  //Render the entity's symbol
            }
            else
            {
                //Otherwise, render the ground tile
                output += "\x1B[33m.";
            }
        }
        output += "\n";
    }

    onMapSubViewUpdated(id, output);
}
