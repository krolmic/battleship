#include "game_guest.h"

// MODEL::GameGuest::GameGuest(const std::string& address, int port)
//     : conn{  address, port,
//                 [&](const QByteArray& data) { qDebug() << "GameGuest::wow data received" << QString::fromUtf8(data); },
//                 [&]() { qDebug() << "GameGuest::wow it works?"; }}
// {
//     
// }

MODEL::GameGuest::GameGuest(const std::string& address, int port, 
                            std::vector<std::reference_wrapper<BattleshipObserver>>& observerList)
    : MODEL::Game{address, port, observerList}
{
    
}


void MODEL::GameGuest::socketConnected()
{
    qDebug() << "MODEL::GameGuest::socketConnected()";
}

