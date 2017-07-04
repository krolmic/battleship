#include "game_guest.h"

MODEL::GameGuest::GameGuest(const std::string& address, int port)
    : conn{  address, port,
                [&](const QByteArray& data) { qDebug() << "GameGuest::wow data received" << QString::fromUtf8(data); },
                [&]() { qDebug() << "GameGuest::wow it works?"; }}
{
    
}

