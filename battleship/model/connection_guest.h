#ifndef CONNECTION_GUEST_H
#define CONNECTION_GUEST_H

#include "connection.h"
#include <string>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>

class QNetworkSession;

namespace MODEL {
class ConnectionGuest : public QObject, public Connection //https://stackoverflow.com/questions/8578657/qobject-multiple-inheritance
{
    Q_OBJECT

public:
    explicit ConnectionGuest(const std::string& address, int port, QObject* parent = nullptr);
    ConnectionGuest(ConnectionGuest const &) = delete; //disable copy-constructor
    ConnectionGuest& operator=(ConnectionGuest const &other) = delete; //disable assign-operator
    ConnectionGuest(ConnectionGuest&& other) = delete; //disable move-constructor
    ConnectionGuest& operator=(ConnectionGuest&& other) = delete; //disable move assign-operator
    
private slots:
    void sessionOpened();
    void readData();
    void displayError(QAbstractSocket::SocketError socketError);
    void connected();
    
private:
    std::string address;
    int port;
    QNetworkSession *networkSession{nullptr};
    QTcpSocket tcpSocket;
    quint16 blockSize{0};
};

} // NS MODEL
#endif // CONNECTION_GUEST_H
