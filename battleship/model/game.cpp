#include "game.h"
#include <QDebug>
#include "common/battleship_observer.h"
#include "common/user_info.h"


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

void MODEL::Game::socketConnected()
{
    qDebug() << "MODEL::Game::socketConnected()";
    for (BattleshipObserver& observer : observerList) {
        observer.shipPlacementStarted();
    }
    com.sendUserInfo(me.getUserInfo());
}



MODEL::Game::~Game()
{
    qDebug() << "~Game dtor";
}

