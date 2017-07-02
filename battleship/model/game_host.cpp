#include "game_host.h"

MODEL::GameHost::GameHost()
    : conn{}
{
    
}

MODEL::Connection& MODEL::GameHost::getConnection()
{
    return conn;
}
