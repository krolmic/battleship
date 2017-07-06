#ifndef GAMEHOST_H
#define GAMEHOST_H

#include "game.h"
#include "connection_host.h"

namespace MODEL {
/// Inherits Game and make it possible to manage hosts game
class GameHost : public Game
{
public:
    GameHost(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList, UserInfo userInfo);
    
    GameHost(GameHost const &) = delete; //disable copy-constructor
    GameHost& operator=(GameHost const &other) = delete; //disable assign-operator
    GameHost(GameHost&& other) = delete; //disable move-constructor
    GameHost& operator=(GameHost&& other) = delete; //disable move assign-operator
    
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
#endif // GAMEHOST_H
