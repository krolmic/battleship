#include "battleship_controller.h"
#include "common/user_friendly_exception.h"
#include <QString>
#include "common/user_info.h"

BattleshipController::BattleshipController(ModelInterface& model)
    : model{model}, view{GUI::BattleshipView{model, *this}}
{
    model.registerObserver(view);
}

void BattleshipController::startNewGameAsHost(const QString& playerName, const QString& age)
{
    try {
        model.startNewGameAsHost(UserInfo{playerName.toStdString(), age.toInt()});
        view.showWaitingForGuestConnectingDialog();
    } catch (UserFriendlyException& e) {
        view.showErrorMessage(e.what());
    }
}

void BattleshipController::startNewGameAsGuest(const QString& address, const QString& port, const QString& playerName, const QString& age)
{
    try {
        model.startNewGameAsGuest(address.toStdString(), port.toInt(), UserInfo{playerName.toStdString(), age.toInt()});
    } catch (UserFriendlyException& e) {
        view.showErrorMessage(e.what());
    }
}
