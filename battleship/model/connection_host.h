#ifndef CONNECTIONHOST_H
#define CONNECTIONHOST_H

#include "connection.h"
#include <QObject>
#include <QTcpServer>

class QNetworkSession;


namespace MODEL {
class ConnectionHost : public QObject, public Connection //https://stackoverflow.com/questions/8578657/qobject-multiple-inheritance
{
    Q_OBJECT

public:
    ConnectionHost(QObject* parent = nullptr);
    ConnectionHost(ConnectionHost const &) = delete; //disable copy-constructor
    ConnectionHost& operator=(ConnectionHost const &other) = delete; //disable assign-operator
    ConnectionHost(ConnectionHost&& other) = delete; //disable move-constructor
    ConnectionHost& operator=(ConnectionHost&& other) = delete; //disable move assign-operator
    
private slots:
    void sessionOpened();
    void sendFortune();

    
private:
    QTcpServer* tcpServer{nullptr};
    QStringList fortunes;
    QNetworkSession* networkSession{nullptr};
};

} // NS MODEL
#endif // CONNECTIONHOST_H
