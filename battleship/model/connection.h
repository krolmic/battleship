#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QAbstractSocket>
#include <vector>
#include <functional>
 
class QNetworkSession;
class QByteArray;
class QTcpSocket;
class ConnectionObserver;

 
namespace MODEL {
class Connection : public QObject
{
    Q_OBJECT

public:
    /**
     * @param callbackOnDataReceived called when full data blcock is received.
     * @param callbackOnConnected called when connection is established
     */
    explicit Connection(   std::function<void(const QByteArray&)> callbackOnDataReceived,
                                    std::function<void()> callbackOnConnected, 
                                    QObject* parent);
    virtual ~Connection();
    Connection(Connection const &) = delete; //disable copy-constructor
    Connection& operator=(Connection const &other) = delete; //disable assign-operator
    Connection(Connection&& other) = delete; //disable move-constructor
    Connection& operator=(Connection&& other) = delete; //disable move assign-operator
    
    void sendData(const QByteArray& data);
    
protected:
    void readData();
    
private slots:
    void sessionOpened();

protected:
    void initNetworkSession();
    virtual void beginConnecting() = 0;
    void displayError(QAbstractSocket::SocketError socketError);
    
    QTcpSocket* socket{nullptr};
    quint16 blockSize{0};
    std::function<void(const QByteArray&)> callbackOnDataReceived;
    std::function<void()> callbackOnConnected;
    
private:

    
    QNetworkSession* networkSession{nullptr};
    
};

} // NS MODEL
#endif // CONNECTION_H
