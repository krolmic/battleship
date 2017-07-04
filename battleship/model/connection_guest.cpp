#include "connection_guest.h"

#include <QDataStream>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>
// #include <QAbstractSocketErrorSignal>

MODEL::ConnectionGuest::ConnectionGuest(  const std::string& address, 
                                            int port,
                                            std::function<void(const QByteArray&)> callbackOnDataReceived,
                                            std::function<void()> callbackOnConnected, 
                                            QObject* parent)
    : MODEL::Connection{callbackOnDataReceived, callbackOnConnected, parent}, address{address}, port{port}
{
    initNetworkSession();
}

void MODEL::ConnectionGuest::beginConnecting()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QString::fromStdString(address), static_cast<quint16>(port));
    connect(socket, &QAbstractSocket::connected, [&]() { callbackOnConnected(); });
    connect(socket, &QIODevice::readyRead, [&]() { readData(); });
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(socket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &ConnectionGuest::displayError);
}

// void MODEL::ConnectionGuest::sessionOpened()
// {
//     if (networkSession) {
//         // Save the used configuration
//         QNetworkConfiguration config = networkSession->configuration();
//         QString id;
//         if (config.type() == QNetworkConfiguration::UserChoice)
//             id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
//         else
//             id = config.identifier();
// 
//         QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
//         settings.beginGroup(QLatin1String("QtNetwork"));
//         settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
//         settings.endGroup();
//     }
//     
//     tcpSocket.connectToHost(QString::fromStdString(address), static_cast<quint16>(port));
// 
//     qDebug() << "This examples requires that you run the  Fortune Server example as well.";
// }


// void MODEL::ConnectionGuest::readData()
// {
//     qDebug() << "MODEL::ConnectionGuest::readData()";
//     QDataStream in(&tcpSocket);
//     in.setVersion(QDataStream::Qt_4_0);
// 
//     if (blockSize == 0) {
//         if (tcpSocket.bytesAvailable() < (int)sizeof(quint16)) {
//             return;
//         }
// 
//         in >> blockSize;
//     }
// 
//     if (tcpSocket.bytesAvailable() < blockSize) {
//         return;
//     }
//     
//     //now complete message have been read
//     blockSize = 0;
//     QString nextMessage;
//     in >> nextMessage;
//     qDebug() << "data received: " << nextMessage;
// }
// 
// void MODEL::ConnectionGuest::displayError(QAbstractSocket::SocketError socketError)
// {
//     qDebug() << "MODEL::ConnectionGuest::displayError()";
//     
//     switch (socketError) {
//     case QAbstractSocket::RemoteHostClosedError:
//         qDebug() << "Fuck you Tutorial for ignoring RemoteHostClosedError.";
//         break;
//     case QAbstractSocket::HostNotFoundError:
//         qDebug() << "The host was not found.";
//         break;
//     case QAbstractSocket::ConnectionRefusedError:
//         qDebug() << "The connection was refused by the peer.";
//         break;
//     default:
//         qDebug() << "The following error occurred: "<< tcpSocket.errorString();
//     }
// }
