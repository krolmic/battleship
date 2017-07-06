#include "battleship_controller.h"
#include "common/user_friendly_exception.h"
#include <QString>
#include <QPoint>
#include "model/point.h"
#include "common/user_info.h"

BattleshipController::BattleshipController(ModelInterface& model)
    : model{model}, view{GUI::BattleshipView{model, *this}}
{
    model.registerObserver(view);
}

bool BattleshipController::placeShip(const QPoint& p1, const QPoint p2)
{
    MODEL::Point mp1{
        static_cast<double>(p1.x()), 
        static_cast<double>(p1.y())
    };
    MODEL::Point mp2{
        static_cast<double>(p2.x()), 
        static_cast<double>(p2.y())
    };
    return model.placeShip(mp1, mp2);
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
