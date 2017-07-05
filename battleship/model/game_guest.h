#ifndef GAMEGUEST_H
#define GAMEGUEST_H

#include "game.h"
#include "connection_guest.h"

class UserInfo;

namespace MODEL {
class GameGuest : public Game
{
public:
    explicit GameGuest(
        const std::string& address, 
        int port, 
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo userInfo);
    
    GameGuest(GameGuest const &) = delete; //disable copy-constructor
    GameGuest& operator=(GameGuest const &other) = delete; //disable assign-operator
    GameGuest(GameGuest&& other) = delete; //disable move-constructor
    GameGuest& operator=(GameGuest&& other) = delete; //disable move assign-operator
    
protected:
//     void socketConnected();
    
};

} // NS MODEL
#endif // GAMEGUEST_H
