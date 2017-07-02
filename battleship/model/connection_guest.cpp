#include "connection_guest.h"

#include <QDataStream>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>

MODEL::ConnectionGuest::ConnectionGuest(const std::string& address, int port, QObject* parent)
    : QObject{parent}, address{address}, port{port}, tcpSocket(new QTcpSocket())
{
    qDebug() << "MODEL::ConnectionGuest ctor";
    
    connect(&tcpSocket, &QTcpSocket::readyRead, this, &ConnectionGuest::readData);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(&tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &ConnectionGuest::displayError);
    
    QNetworkConfigurationManager manager; //just wondering if this shiat is required at all?
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
        connect(networkSession, &QNetworkSession::opened, this, &ConnectionGuest::sessionOpened);

        qDebug() << "Opening network session.";
        networkSession->open();
    } else {
        sessionOpened();
    }
    
//     tcpSocket.connectToHost(QString::fromStdString(address), static_cast<quint16>(port));
}

void MODEL::ConnectionGuest::sessionOpened()
{
    if (networkSession) {
        // Save the used configuration
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
    
    tcpSocket.connectToHost(QString::fromStdString(address), static_cast<quint16>(port));

    qDebug() << "This examples requires that you run the  Fortune Server example as well.";
}


void MODEL::ConnectionGuest::readData()
{
    qDebug() << "MODEL::ConnectionGuest::readData()";
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }

        in >> blockSize;
    }

    if (tcpSocket.bytesAvailable() < blockSize) {
        return;
    }
    
    //now complete message have been read
    blockSize = 0;
    QString nextMessage;
    in >> nextMessage;
    qDebug() << "data received: " << nextMessage;
}

void MODEL::ConnectionGuest::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "MODEL::ConnectionGuest::displayError()";
    
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
        qDebug() << "The following error occurred: "<< tcpSocket.errorString();
    }
}

void MODEL::ConnectionGuest::connected()
{
    qDebug() << "MODEL::ConnectionGuest::connected()";
}
