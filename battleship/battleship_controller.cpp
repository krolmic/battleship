#include "battleship_controller.h"
#include "common/user_friendly_exception.h"

BattleshipController::BattleshipController(ModelInterface& model)
    : model{model}, view{GUI::BattleshipView{model, *this}}
{
    model.registerObserver(view);
}

void BattleshipController::startNewGameAsHost(const std::string& playerName, int age)
{
    try {
        model.startNewGameAsHost(playerName, age);
        view.showWaitingForGuestConnectingDialog();
    } catch (UserFriendlyException& e) {
        view.showErrorMessage(e.what());
    }
}

void BattleshipController::startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age)
{
    model.startNewGameAsGuest(address, port, playerName, age);
}
