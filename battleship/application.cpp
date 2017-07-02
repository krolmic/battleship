#include "application.h"
#include "model/game_guest.h"
#include "model/game_host.h"

Application::Application()
{

}


/**
 * @brief start game as a host wating client-guest to connect to
 */
void Application::startNewGameAsHost()
{
    game.reset(new MODEL::GameHost{}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}

/**
 * @brief starts new game session and also connects to a host
 * @param address ipv4 address
 * @param port a port number
 */
void Application::startNewGameAsGuest(const std::string& address, int port)
{
    game.reset(new MODEL::GameGuest{address, port}); //stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr
}
