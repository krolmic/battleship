#ifndef GAMEHOST_H
#define GAMEHOST_H

#include "game.h"
#include "connection_host.h"

namespace MODEL {
class GameHost : public Game
{
public:
    GameHost(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList, UserInfo userInfo);
    
    GameHost(GameHost const &) = delete; //disable copy-constructor
    GameHost& operator=(GameHost const &other) = delete; //disable assign-operator
    GameHost(GameHost&& other) = delete; //disable move-constructor
    GameHost& operator=(GameHost&& other) = delete; //disable move assign-operator
    
protected:
//     void socketConnected();
};

} // NS MODEL
#endif // GAMEHOST_H
