#include "game_host.h"

#include <QDebug>
#include "common/battleship_observer.h"

MODEL::GameHost::GameHost(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList)
    : MODEL::Game{observerList}
{
    
}

// void MODEL::GameHost::connected()
// {
//     qDebug() << "GameHost::connected"; 
//     QByteArray block = QString::fromStdString("letz tranzferz $$$$$$").toUtf8();
//     conn.sendData(block);
// }

void MODEL::GameHost::socketConnected()
{
    qDebug() << "MODEL::GameHost::socketConnected()";
    //TODO startTimer (only on host side
//     observer.shipPlacementStarted();
    for (BattleshipObserver& observer : observerList) {
        observer.shipPlacementStarted();
    }
}
