#include "game_host.h"

#include <QDebug>
#include "common/battleship_observer.h"
#include "common/user_info.h"

MODEL::GameHost::GameHost(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList, UserInfo userInfo)
    : MODEL::Game{observerList, userInfo}
{
    
}

// void MODEL::GameHost::socketConnected()
// {
//     qDebug() << "MODEL::GameHost::socketConnected()";
//     for (BattleshipObserver& observer : observerList) {
//         observer.shipPlacementStarted();
//     }
// }
