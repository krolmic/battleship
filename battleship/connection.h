#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
 

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection();
    void connect();

private:
    QTcpSocket *tcpSocket;
};

#endif // CONNECTION_H
