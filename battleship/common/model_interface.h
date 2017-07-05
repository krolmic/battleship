#ifndef MODELINTERFACE_H
#define MODELINTERFACE_H

#include <string>

class BattleshipObserver;
class UserInfo;

namespace MODEL {
    class Point;
}
/// The base class that defines the model interface
class ModelInterface //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~ModelInterface () { }
    
    /**
     * Observer pattern as a part of MVC-Pattern
     * @param observer is usally a gui, that reflects/shows state-changes of the model
     */
    virtual void registerObserver(BattleshipObserver& observer) = 0;
    
    /**
     * begin new game as host over the network. But first wat for guest  to join.
     */
    virtual void startNewGameAsHost(UserInfo userInfo) = 0;
    
    
    /**
     * connect to a host as a guest over the network
     * @param address ipv4 address
     * @param port a port number
     * @param playerName a name, like firstname
     * @param age biological age of a human player
     */
    virtual void startNewGameAsGuest(const std::string& address, int port, UserInfo userInfo) = 0;
    
    
    /**
     * user can stop while hosting game and waiting for others to join his game.
     * This is the case after ModelInterface#startNewGameAsHost(const std::string&, int) call
     */
    virtual void cancelHosting() = 0;
    
    /**
     * @throws std::length_error if ship count exceeds 5.
     */
    virtual void placeShip(MODEL::Point p1, MODEL::Point p2) = 0;
    
    
    
};

#endif // MODELINTERFACE_H
