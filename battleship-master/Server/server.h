#ifndef SERVER_H
#define SERVER_H

#include <QStringList>
#include <QTcpServer>

//! [0]
class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    QStringList s;
};
//! [0]

#endif
