#include "game.h"
#include "common/battleship_observer.h"
#include "common/user_info.h"
#include "point.h"
#include <QString>
#include <QJsonArray>

#include <QDebug>


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


MODEL::Player& MODEL::Game::getPlayerMe()
{
    return me;
}

MODEL::Player& MODEL::Game::getPlayerEnemy()
{
    return enemy;
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
    com.sendUserInfo(me.getUserInfo());
}

void MODEL::Game::addShipListToEnemy(const QJsonArray& json)
{
    for (int i = 0; i < json.size(); ++i) {
        QJsonObject ship = json[i].toObject();
        enemy.getField().addShip(
            MODEL::Point{ship["x1"].toDouble(), ship["y1"].toDouble()},
            MODEL::Point{ship["x2"].toDouble(), ship["y2"].toDouble()}
        );
    }
}

bool MODEL::Game::placeShip(MODEL::Point p1, MODEL::Point p2)
{
    bool allShipSet = me.getField().addShip(p1, p2);
//     if (allShipSet) {
//         //gui is deactivated since it get return value
//         //but here we send our command to enemy
//         com.sendPlacedShipList(me.getField());
//     }
    
    return allShipSet;
}

