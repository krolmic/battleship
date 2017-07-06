#ifndef BATTLESHIPOBSERVER_H
#define BATTLESHIPOBSERVER_H

#include <deque>

namespace MODEL {
class Ship;
}

class UserInfo;

/// A base interface class, includes methods, which communicate with model and gui
class BattleshipObserver //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~BattleshipObserver () { }
    
    /**
     * we received placed ships from enemy. Anwe get
     * Now it's time to possibly to start a game?
     */
    virtual void onGameStart(
        const std::deque<MODEL::Ship>& me, 
        const std::deque<MODEL::Ship>& enemy,
        bool myTurn) = 0;
    
    /**
     * received UserInfo from enemy after players have connected
     * now it's time to place ships
     */
    virtual void onRcvUserInfo(const UserInfo& me, const UserInfo& enemy) = 0;
    
    //std::deque<MODEL::Ship>&
    
};


#endif // BATTLESHIPOBSERVER_H
