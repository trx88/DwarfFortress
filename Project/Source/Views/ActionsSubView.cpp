#include "ActionsSubView.h"
#include "../Domains/Entities/Player.h"
#include <string>

ActionsSubView::ActionsSubView(int id, std::shared_ptr<class Player> player)
{
	this->id = id;
	player->onPlayerActionMessageUpdated.connect([this](PlayerActionsDataModel* playerActionsDataModel) {UpdateSubView(playerActionsDataModel); });
}

void ActionsSubView::UpdateSubView(PlayerActionsDataModel* playerActionsDataModel)
{
    std::string output;

    //Adding spaces to avoid clearing the console since it flickers.
    std::string emptyTextTitle = "                ";
    std::string emptyTextGameState = "              ";
    std::string emptyTextGameAction = "              ";

    output += "\x1B[92m--ACTIONS--" + emptyTextTitle + "\n";
    
    output += playerActionsDataModel->GetGameState() + emptyTextGameState;
    output += "\n";
    output += playerActionsDataModel->GetGameAction() + emptyTextGameAction;
    output += "\n";

    onActionsSubViewUpdated(id, output);
}
