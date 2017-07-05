#ifndef PLAYER_H
#define PLAYER_H

#include "common/user_info.h"

namespace MODEL {

class Player
{
public:
    Player();
    Player(const UserInfo& userInfo);
    
    Player(Player const &) = delete; //disable copy-constructor
    Player& operator=(Player const &other) = delete; //disable assign-operator
    Player(Player&& other) = delete; //disable move-constructor
    Player& operator=(Player&& other) = delete; //disable move assign-operator
    
    void setUserInfo(const UserInfo& userInfo);
    const UserInfo& getUserInfo();
    
private:
    UserInfo userInfo;
};

} // end NS
#endif // PLAYER_H
