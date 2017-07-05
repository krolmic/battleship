#ifndef CONNECTIONHOST_H
#define CONNECTIONHOST_H

#include "connection.h"

class QNetworkSession;
class QTcpServer;


namespace MODEL {
/// Inherits from Connection and implements the functionality for connection used by host
class ConnectionHost : public Connection //https://stackoverflow.com/questions/8578657/qobject-multiple-inheritance
{
    Q_OBJECT

public:
    /**
     * @param callbackOnDataReceived called when full data blcock is received.
     * @param callbackOnConnected called when connection is established
     */
    explicit ConnectionHost(    std::function<void(const QByteArray&)> callbackOnDataReceived,
                                            std::function<void()> callbackOnConnected, 
                                            QObject* parent = nullptr);
    ~ConnectionHost();
    ConnectionHost(ConnectionHost const &) = delete; //disable copy-constructor
    ConnectionHost& operator=(ConnectionHost const &other) = delete; //disable assign-operator
    ConnectionHost(ConnectionHost&& other) = delete; //disable move-constructor
    ConnectionHost& operator=(ConnectionHost&& other) = delete; //disable move assign-operator
    
protected:
    void beginConnecting() override;
    
private:
    QTcpServer* tcpServer{nullptr};
};

} // NS MODEL
#endif // CONNECTIONHOST_H
