#include "connection.h"

#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>
#include <QDataStream>
#include <QTcpSocket>


MODEL::Connection::Connection( std::function<void(const QByteArray&)> callbackOnDataReceived, 
                                                std::function<void()> callbackOnConnected, 
                                                QObject* parent)
    : QObject{parent}, callbackOnDataReceived{callbackOnDataReceived}, callbackOnConnected{callbackOnConnected}
{
    
}

MODEL::Connection::~Connection()
{
    if (socket) {
        socket->disconnectFromHost();
    }
}


void MODEL::Connection::initNetworkSession()
{
    QNetworkConfigurationManager manager{};

    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProjectBattleship"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &Connection::sessionOpened);

        qDebug() << "Opening network session.";
        networkSession->open();
    } else {
        sessionOpened();
    }
}

void MODEL::Connection::sessionOpened()
{
     // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }
    
    beginConnecting();
}

void MODEL::Connection::sendData(const QByteArray& data)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0 << data;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    socket->write(block);
}

// void MODEL::Connection::registerObserver(ConnectionObserver& observer)
// {
//     observerList.emplace_back(observer);
// }
// void MODEL::Connection::addHandlerConnected(std::function<void()> callback)
// {
//     handlerConnectedList.emplace_back(callback);
// }
// void MODEL::Connection::emitEventConnected()
// {
//     qDebug() << "emitEventConnected !";
//     
// //     for (auto& observer : handlerConnectedList) {
// //         observer();
// //     }
// //     for (ConnectionObserver& observer : observerList) {
// //         observer.connectionEstablished();
// //     }
// }

void MODEL::Connection::readData()
{
    qDebug() << "MODEL::Connection::readData()";
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }

        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize) {
        return;
    }
    
    //now complete message have been read
    blockSize = 0;

    QByteArray bytes;
    in >> bytes;
    callbackOnDataReceived(bytes);
//     qDebug() << "data received: " << QString::fromUtf8(bytes);
}

void MODEL::Connection::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "NETZZZ WOKRZ displayError()";
    
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "Fuck you Tutorial for ignoring RemoteHostClosedError.";
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer.";
        break;
    default:
        qDebug() << "The following error occurred: "<< socket->errorString();
    }
}













