#include "connection.h"

Connection::Connection()
    : tcpSocket(new QTcpSocket(this))
{
}

void Connection::connect()
{
//     getFortuneButton->setEnabled(false);
    tcpSocket->abort();
    tcpSocket->connectToHost("localhost", 2077);
}

