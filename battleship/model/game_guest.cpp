#include "game_guest.h"
#include "common/user_info.h"

// MODEL::GameGuest::GameGuest(const std::string& address, int port)
//     : conn{  address, port,
//                 [&](const QByteArray& data) { qDebug() << "GameGuest::wow data received" << QString::fromUtf8(data); },
//                 [&]() { qDebug() << "GameGuest::wow it works?"; }}
// {
//     
// }

MODEL::GameGuest::GameGuest(
        const std::string& address, 
        int port, 
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList,
        UserInfo userInfo)
    : MODEL::Game{address, port, observerList, userInfo}
{
    
}


// void MODEL::GameGuest::socketConnected()
// {
//     qDebug() << "MODEL::GameGuest::socketConnected()";
// }

