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
                                                                  [&](const QByteArray& data) {recieveData(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{
    //std::bind(&MODEL::Communicator::dataReceived, this)
}

MODEL::Communicator::Communicator(   MODEL::Game& game,
                                     std::function<void()> callbackOnConnected)
    : game{game}, conn{ std::make_unique<MODEL::ConnectionHost>(
                            [&](const QByteArray& data) {recieveData(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{
    //std::bind(&MODEL::Communicator::dataReceived, this)
}

void MODEL::Communicator::recieveData(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = doc.object();
    objectType type = static_cast<objectType>(jsonObject["type"].toInt());
    QJsonObject object = jsonObject["object"].toObject();

    switch(type)
    {
    case objectType::result:
        // use jsonarray and create objects of attackResult
        break;
    case objectType::attack:
        // same
        break;
    case objectType::player:
        // TODO: change constructor in Player class
        // there is not need for QString pointer
        Player p(object["name"].toString(),object["PropertyName"].toInt());
        break;
    case objectType::timeout:
        break;
    }
}
