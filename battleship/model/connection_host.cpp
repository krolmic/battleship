#include "connection_host.h"
#include "common/user_friendly_exception.h"
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>
#include <QTcpSocket>
#include <QTcpServer>

#include <QDataStream> //TODO remove


MODEL::ConnectionHost::ConnectionHost( std::function<void(const QByteArray&)> callbackOnDataReceived,
                                                            std::function<void()> callbackOnConnected, 
                                                            QObject* parent)
    : MODEL::Connection{callbackOnDataReceived, callbackOnConnected, parent}
{
    initNetworkSession();
    //TODO when disconnected?

}

MODEL::ConnectionHost::~ConnectionHost()
{
    qDebug() << "~ConnectionHost() dtor";
    //todo disconnect gracefully
}

void MODEL::ConnectionHost::beginConnecting()
{
    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen(QHostAddress::Any, 3570)) {
        throw UserFriendlyException{"Unable to start the server: " + tcpServer->errorString().toStdString()};
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) { //use the first non-localhost IPv4 address
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty()) { // if we did not find one, use IPv4 localhost
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    connect(tcpServer, &QTcpServer::newConnection, [&]() {
        qDebug() << "QTcpServer::newConnection";
        socket = tcpServer->nextPendingConnection();
        callbackOnConnected();
        tcpServer->close();
    });
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(socket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &ConnectionHost::displayError);
    
    
    qDebug() << "The server is running on\n\nIP: " << ipAddress
                  << "\nport: " << tcpServer->serverPort() <<  "\n\nRun the Fortune Client example now.";
}




