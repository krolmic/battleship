#include "server.h"
#include "thread.h"

#include <stdlib.h>

//! [0]
Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    s << tr("Connected to Server");
}
//! [0]

//! [1]
void Server::incomingConnection(qintptr socketDescriptor)
{
    QString s1 = s.at(qrand() % s.size());
    Thread *thread = new Thread(socketDescriptor, s1, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
//! [1]
