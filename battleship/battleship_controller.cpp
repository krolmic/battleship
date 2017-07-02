#include "battleship_controller.h"
#include "gui/battleship_view.h"

BattleshipController::BattleshipController(ModelInterface& model)
    : model{model}, view{new GUI::BattleshipView{model, *this}}
{
}

void BattleshipController::startNewGameAsHost(const std::string& playerName, int age)
{
    model.startNewGameAsHost(playerName, age);
    view->showWaitingForGuestConnectingDialog();
}

void BattleshipController::startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age)
{
    model.startNewGameAsGuest(address, port, playerName, age);
}
