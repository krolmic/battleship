#ifndef BATTLESHIPOBSERVER_H
#define BATTLESHIPOBSERVER_H

class UserInfo;

class BattleshipObserver //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~BattleshipObserver () { }
    
    
    /**
     * received UserInfo from enemy after players have connected
     * now it's time to place ships
     */
    virtual void onRcvUserInfo(const UserInfo& me, const UserInfo& enemy) = 0;
    
};


#endif // BATTLESHIPOBSERVER_H
