#include "player.h"

MODEL::Player::Player()
    : userInfo{}
{

}

MODEL::Player::Player(const UserInfo& userInfo)
    : userInfo{userInfo}
{

}

void MODEL::Player::setUserInfo(const UserInfo& userInfo)
{
    this->userInfo = userInfo;
}

const UserInfo& MODEL::Player::getUserInfo()
{
    return userInfo;
}



