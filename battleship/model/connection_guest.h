#ifndef CONNECTION_GUEST_H
#define CONNECTION_GUEST_H

#include "connection.h"
#include <string>
#include <QTcpSocket>
#include <QAbstractSocket>

class QNetworkSession;

namespace MODEL {
/// Inherits from Connection and implements the functionality for connection used by guest
class ConnectionGuest : public Connection //https://stackoverflow.com/questions/8578657/qobject-multiple-inheritance
{
    Q_OBJECT

public:
    /**
     * @param callbackOnDataReceived called when full data blcock is received.
     * @param callbackOnConnected called when connection is established
     */
    explicit ConnectionGuest(  const std::string& address, 
                                            int port,
                                            std::function<void(const QByteArray&)> callbackOnDataReceived,
                                            std::function<void()> callbackOnConnected, 
                                            QObject* parent = nullptr);
    
    
    ConnectionGuest(ConnectionGuest const &) = delete; //disable copy-constructor
    ConnectionGuest& operator=(ConnectionGuest const &other) = delete; //disable assign-operator
    ConnectionGuest(ConnectionGuest&& other) = delete; //disable move-constructor
    ConnectionGuest& operator=(ConnectionGuest&& other) = delete; //disable move assign-operator

protected:
    void beginConnecting() override;

private slots:
//     void readData();
    
private:
    std::string address;
    int port;
};

} // NS MODEL
#endif // CONNECTION_GUEST_H
