#include "game_host.h"

#include <QDebug>
#include "common/battleship_observer.h"
#include "common/user_info.h"
#include <cstdlib>
#include <ctime>

MODEL::GameHost::GameHost(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList, UserInfo userInfo)
    : MODEL::Game{observerList, userInfo}
{
    std::srand(std::time(0)); // use current time as seed for random generator
    myTurn = (std::rand() % 2 == 1);
}

void MODEL::GameHost::onRcvShipPlacement(const QJsonValue& json)
{
    addShipListToEnemy(json.toArray()); //as host we get from guest just list of ships without whos next turn;
    
    if (me.getField().isAllShipPlaced()) { //if I am also ready
        for (BattleshipObserver& observer : observerList) {
            observer.onGameStart(
                    me.getField().getShipList(),
                    enemy.getField().getShipList(),
                    myTurn);
        }
    }
}

bool MODEL::GameHost::placeShip(MODEL::Point p1, MODEL::Point p2)
{
//     qDebug() << "GameHost::placeShip() ~~~~~~~~~~~~~~~~";
    bool allShipSet = Game::placeShip(p1, p2);
    if (allShipSet) {
        com.sendPlacedShipList(me.getField(), myTurn);  //as host we know firsthand whos next turn
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


