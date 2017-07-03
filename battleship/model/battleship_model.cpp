#include "battleship_model.h"
#include "game_guest.h"
#include "game_host.h"

MODEL::BattleshipModel::BattleshipModel()
{

}


void MODEL::BattleshipModel::startNewGameAsHost(const std::string& playerName, int age)
{
    game.reset(new MODEL::GameHost{}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}


void MODEL::BattleshipModel::startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age)
{
    game.reset(new MODEL::GameGuest{address, port}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}

void MODEL::BattleshipModel::cancelHosting()
{
    game.reset(nullptr);
}


