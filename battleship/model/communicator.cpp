#include "communicator.h"
#include "game.h"
#include "connection_guest.h"
#include "connection_host.h"
#include <memory>
#include <QJsonValue>
#include <QJsonDocument>
#include "common/user_info.h"

MODEL::Communicator::Communicator(   MODEL::Game& game,
                                                            const std::string& address, 
                                                            int port,
                                                            std::function<void()> callbackOnConnected)
    : game{game}, conn{ std::make_unique<MODEL::ConnectionGuest>( address, port, 
        [&](const QByteArray& data) {dataReceived(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{

}

MODEL::Communicator::Communicator(   MODEL::Game& game,
                                                            std::function<void()> callbackOnConnected)
    : game{game}, conn{ std::make_unique<MODEL::ConnectionHost>( 
        [&](const QByteArray& data) {dataReceived(data); },callbackOnConnected) } //TODO std::bind doesn't work ?
{

}

void MODEL::Communicator::sendJson(const MODEL::Command& command, const QJsonValue& json)
{

    QJsonObject resultJson{
        {"command", static_cast<int>(command)},
        {"value", json}
    };
    
    QJsonDocument doc(resultJson);
    conn->sendData(doc.toJson());

    qDebug() << "Communicator::sendJson() -> command enum: " << static_cast<int>(command);
}


void MODEL::Communicator::dataReceived(const QByteArray& data)
{
    qDebug() << "COMM::dataReceived: " << data;
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) { // hat es geklappt?
        throw std::runtime_error{"JSON-Format nicht erkannt"};
    }
    if (!doc.isObject()) {
        throw std::runtime_error{"QJsonDocument enthaelt mehrere Objekte"};
    }
    QJsonObject jsonTotal{ doc.object() };
//     int command{ jsonTotal["command"].toInt() };
    Command command{ static_cast<Command>(jsonTotal["command"].toInt()) };
    QJsonValue jsonValue{ jsonTotal["value"] };
    qDebug() << "command enum as int: " << static_cast<int>(command);
    qDebug() << "json received: " << jsonValue;
    switch (command) {
        case Command::USER_INFO : 
        {
            UserInfo enemyUserInfo{jsonValue.toObject()};
            game.onRcvUserInfo(enemyUserInfo);
            break;
        }
        case Command::PLACED_SHIP_LIST :
            game.onRcvShipPlacement(jsonValue);
            break;
    }
    
}


void MODEL::Communicator::sendUserInfo(const UserInfo& userInfo)
{
    sendJson(MODEL::Command::USER_INFO, userInfo.toJson());
}

void MODEL::Communicator::sendPlacedShipList(const MODEL::CoordinateSystem& myField)
{
    sendJson(MODEL::Command::PLACED_SHIP_LIST, myField.getShipListAsJson());
}

void MODEL::Communicator::sendPlacedShipList(const MODEL::CoordinateSystem& myField, bool hostTurn)
{
    QJsonObject json {
        {"host_turn", hostTurn },
        {"field", myField.getShipListAsJson()}
    };
    sendJson(MODEL::Command::PLACED_SHIP_LIST, json);
}














