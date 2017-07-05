#ifndef GAME_H
#define GAME_H

#include "communicator.h"
#include "model/player.h"
#include <vector>

class BattleshipObserver;
class UserInfo;

namespace MODEL {
    
class Point;
/// A class representing game session that access both Player and Communicator
class Game
{
public:
    virtual ~Game();
    

    
    /**
     * received UserInfo from enemy after players have connected
     */
    void onRcvUserInfo(const UserInfo& userInfo);
    
    /**
     * received all ships of the enemy after placement,
     * now it's time to reconstruct the ships of the enemy locally
     */
    void onRcvShipPlacement(const std::vector<std::pair<Point, Point>> rawShipList);
    
    /**
     * @see ModelInterface#placeShip(MODEL::Point, MODEL::Point)
     */
    void placeShip(Point p1, Point p2);
    
protected:
    /**
     * constructor used in GameHost class
     */
    explicit Game(
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList, 
        UserInfo UserInfo);

    /**
     * constructor used in GameGuest class
     */
    explicit Game(
        const std::string& address, 
        int port,
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo UserInfo
    );
    
    
    Game(Game const &) = delete; //disable copy-constructor
    Game& operator=(Game const &other) = delete; //disable assign-operator
    Game(Game&& other) = delete; //disable move-constructor
    Game& operator=(Game&& other) = delete; //disable move assign-operator
    
    
    
protected:
    void socketConnected();
    std::vector<std::reference_wrapper<BattleshipObserver>>& observerList;
    
    MODEL::Player me;
    MODEL::Player enemy;
    
private:
    Communicator com;
};

} // NS MODEL
#endif // GAME_H
