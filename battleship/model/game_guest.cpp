#include "game_guest.h"
#include "common/user_info.h"
#include "common/battleship_observer.h"

// MODEL::GameGuest::GameGuest(const std::string& address, int port)
//     : conn{  address, port,
//                 [&](const QByteArray& data) { qDebug() << "GameGuest::wow data received" << QString::fromUtf8(data); },
//                 [&]() { qDebug() << "GameGuest::wow it works?"; }}
// {
//     
// }

MODEL::GameGuest::GameGuest(
        const std::string& address, 
        int port, 
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo userInfo)
    : MODEL::Game{address, port, observerList, userInfo}
{
    
}

void MODEL::GameGuest::onRcvShipPlacement(const QJsonValue& json)
{
    QJsonObject jsonObj = json.toObject();
    myTurn = !( jsonObj["host_turn"].toBool() ); //if hosts turn, when it's not our turn
    addShipListToEnemy( jsonObj["field"].toArray() );
    
    if (me.getField().isAllShipPlaced()) { //if I am also ready
        for (BattleshipObserver& observer : observerList) {
            observer.onGameStart(
                    me.getField().getShipList(),
                    enemy.getField().getShipList(),
                    myTurn);
        }
    }
}

bool MODEL::GameGuest::placeShip(MODEL::Point p1, MODEL::Point p2)
{
//     qDebug() << "GameHost::placeShip() ~~~~~~~~~~~~~~~~";
    bool allShipSet = Game::placeShip(p1, p2);
    if (allShipSet) {
        com.sendPlacedShipList(me.getField()); //we don't send whos next turn
    }
    
    if (allShipSet && enemy.getField().isAllShipPlaced()) { //if enemy also ready
        for (BattleshipObserver& observer : observerList) {
            observer.onGameStart(
                    me.getField().getShipList(),
                    enemy.getField().getShipList(),
                    myTurn);
        }
    }
    
    return allShipSet;
}





