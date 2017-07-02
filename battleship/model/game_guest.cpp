#include "game_guest.h"

MODEL::GameGuest::GameGuest(const std::string& address, int port)
    : conn{address, port}
{
    
}

MODEL::Connection& MODEL::GameGuest::getConnection()
{
    return conn;
}
