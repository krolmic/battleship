#include "game_host.h"

#include <QDebug>

MODEL::GameHost::GameHost()
    : conn{
            [&](const QByteArray& data) { qDebug() << "wow data received"; },
            std::bind(&GameHost::connected, this)}
{
    
}

void MODEL::GameHost::connected()
{
    qDebug() << "GameHost::connected"; 
    QByteArray block = QString::fromStdString("letz tranzferz $$$$$$").toUtf8();
    conn.sendData(block);
}
