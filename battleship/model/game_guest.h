#ifndef GAMEGUEST_H
#define GAMEGUEST_H

#include "game.h"
#include "connection_guest.h"

namespace MODEL {
class GameGuest : public Game
{
public:
    explicit GameGuest(const std::string& address, int port);
    
    GameGuest(GameGuest const &) = delete; //disable copy-constructor
    GameGuest& operator=(GameGuest const &other) = delete; //disable assign-operator
    GameGuest(GameGuest&& other) = delete; //disable move-constructor
    GameGuest& operator=(GameGuest&& other) = delete; //disable move assign-operator
    
private:
    MODEL::ConnectionGuest conn;
};

} // NS MODEL
#endif // GAMEGUEST_H
