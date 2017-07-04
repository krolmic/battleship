#include "communicator.h"
#include "game.h"
#include "connection_guest.h"
#include "connection_host.h"
#include <memory>

MODEL::Communicator::Communicator(   MODEL::Game& game,
                                                            const std::string& address, 
                                                            int port,
                                                            std::function<void()> callbackOnConnected)
    : game{game}, conn{ std::make_unique<MODEL::ConnectionGuest>( address, port, 
        [&](const QByteArray& data) {dataReceived(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{
    //std::bind(&MODEL::Communicator::dataReceived, this)
}

MODEL::Communicator::Communicator(   MODEL::Game& game,
                                                            std::function<void()> callbackOnConnected)
    : game{game}, conn{ std::make_unique<MODEL::ConnectionHost>( 
        [&](const QByteArray& data) {dataReceived(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{
    //std::bind(&MODEL::Communicator::dataReceived, this)
}


void MODEL::Communicator::dataReceived(const QByteArray& data)
{
    qDebug() << "COMM::dataReceived: " << data;
}
