#include "game.h"
#include <QDebug>
#include "common/battleship_observer.h"
#include "common/user_info.h"
#include "point.h"

#include <QString>


MODEL::Game::Game(
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo userInfo)
    : observerList{observerList},
      me{userInfo},
      com{*this, std::bind(&MODEL::Game::socketConnected, this)}
{
    
}


MODEL::Game::Game(
        const std::string& address, 
        int port,
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo userInfo)
    : observerList{observerList},
      me{userInfo},
      com{*this, address, port, std::bind(&MODEL::Game::socketConnected, this)}
{

}

MODEL::Game::~Game()
{
    qDebug() << "~Game dtor";
}


void MODEL::Game::onRcvUserInfo(const UserInfo& userInfo)
{
    qDebug() << "userInfo: " << QString::fromStdString(userInfo.getName()) << " age: " << userInfo.getAge();
    enemy.setUserInfo(userInfo);
    for (BattleshipObserver& observer : observerList) {
        observer.onRcvUserInfo(me.getUserInfo(), enemy.getUserInfo());
    }
}

void MODEL::Game::socketConnected()
{
    qDebug() << "MODEL::Game::socketConnected() : me: " << QString::fromStdString(me.getUserInfo().getName());
//     for (BattleshipObserver& observer : observerList) {
//         observer.shipPlacementStarted();
//     }
    com.sendUserInfo(me.getUserInfo());
}

void MODEL::Game::onRcvShipPlacement(const std::vector<std::pair<Point, Point> > rawShipList)
{
    for (auto& e: rawShipList) {
        enemy.getField().addShip(e.first, e.second); //reconstruct the ships of enemy (over network)
    }
    
//     for (BattleshipObserver& observer : observerList) {
//         observer.shipPlacementStarted();
//     }
}


void MODEL::Game::placeShip(MODEL::Point p1, MODEL::Point p2)
{
    if (me.getField().addShip(p1, p2)) {
        //TODO fire event, all ships are placed
    }
}

