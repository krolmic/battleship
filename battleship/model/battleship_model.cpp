#include "battleship_model.h"
#include "game_guest.h"
#include "game_host.h"
#include "common/user_info.h"
#include "point.h"

MODEL::BattleshipModel::BattleshipModel()
{

}


void MODEL::BattleshipModel::registerObserver(BattleshipObserver& observer)
{
    observerList.emplace_back(observer);
}

void MODEL::BattleshipModel::startNewGameAsHost(UserInfo userInfo)
{
    game.reset(new MODEL::GameHost{observerList, userInfo}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}


void MODEL::BattleshipModel::startNewGameAsGuest(const std::string& address, int port, UserInfo userInfo)
{
    game.reset(new MODEL::GameGuest{address, port, observerList, userInfo}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}

void MODEL::BattleshipModel::cancelHosting()
{
    game.reset(nullptr);
}

void MODEL::BattleshipModel::placeShip(MODEL::Point p1, MODEL::Point p2)
{
    game->placeShip(p1, p2);
}






