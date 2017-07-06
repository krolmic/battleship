#ifndef GAMEGUEST_H
#define GAMEGUEST_H

#include "game.h"
#include "connection_guest.h"

class UserInfo;

namespace MODEL {
/// Inherits Game and make it possible to manage guests game
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
    
    
    /**
     * received all ships of the enemy after placement,
     * now it's time to reconstruct the ships of the enemy locally
     * and start the game if I am also ready with ship placement
     */
    void onRcvShipPlacement(const QJsonValue& json) override;
    
    /**
     * @see ModelInterface#placeShip(MODEL::Point, MODEL::Point)
     * behaviour is diffferent for Host and Guest, since Host decides whos next turn
     */
    virtual bool placeShip(Point p1, Point p2);
    
protected:
//     void socketConnected();
    
};

} // NS MODEL
#endif // GAMEGUEST_H
