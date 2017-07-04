#include "game.h"
#include <QDebug>
#include "common/battleship_observer.h"

// MODEL::Game::Game()
// {
// 
// }

// MODEL::Game::Game(std::function<void ()> callbackOnConnected)
//     : com{*this, std::bind(&MODEL::Game::socketConnected, this)}
// {
// }
// 
// 
// MODEL::Game::Game(    const std::string& address, 
//                                     int port,
//                                     std::function<void()> callbackOnConnected)
//     : com{*this, address, port, std::bind(&MODEL::Game::socketConnected, this)}
// {
// 
// }

MODEL::Game::Game(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList)
    : observerList{observerList}, com{*this, std::bind(&MODEL::Game::socketConnected, this)}
{
}


MODEL::Game::Game(const std::string& address, int port,
    std::vector<std::reference_wrapper<BattleshipObserver>>& observerList
)
    : observerList{observerList}, com{*this, address, port, std::bind(&MODEL::Game::socketConnected, this)}
{

}

void MODEL::Game::socketConnected()
{
    qDebug() << "MODEL::Game::socketConnected()";
}



MODEL::Game::~Game()
{
    qDebug() << "~Game dtor";
}

