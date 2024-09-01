#include "StatsSubView.h"
#include "../Domains/Entities/Player.h"
#include <string>

StatsSubView::StatsSubView(int id, std::shared_ptr<class Player> player)
{
    this->id = id;
    player->onPlayerStatsUpdated.connect([this](EntityStatsDataModel* entityStatsModel) {UpdateSubView(entityStatsModel); });
}

void StatsSubView::UpdateSubView(EntityStatsDataModel* entityStatsDataModel)
{
    std::string output;

    output += "\x1B[92m---STATS---\n";
    output += "\x1B[37m"; //Print in white
    output += "HP: ";
    output += std::to_string(entityStatsDataModel->GetHealthPoints());
    output += "\n";
    output += "AP: ";
    output += std::to_string(entityStatsDataModel->GetArmorPoints());
    output += "\n";
    output += "DMG: ";
    output += std::to_string(entityStatsDataModel->GetDamage());
    output += "\n";

    output += "\n";
    onStatsSubViewUpdated(id, output);
}
