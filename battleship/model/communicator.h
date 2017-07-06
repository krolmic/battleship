#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <memory>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "connection.h"

class QJsonValue;
class UserInfo;

namespace MODEL {
    
class Game;
class CoordinateSystem;

enum class Command
{ 
    USER_INFO,
    PLACED_SHIP_LIST
};
/// A class that uses Connection to recieve/send encoded/decoded information stored in json objects
class Communicator
{
public:
    //     explicit Communicator(std::unique_ptr<Connection> conn);
    /**
     * creates commincator as guest
     *
     * @param callbackOnConnected called when connection is established
     */
    explicit Communicator( MODEL::Game& game,
                           const std::string& address,
                           int port,
                           std::function<void()> callbackOnConnected);
    /**
     * creates commincator as host
     *
     * @param callbackOnConnected called when connection is established
     */
    explicit Communicator( MODEL::Game& game,
                           std::function<void()> callbackOnConnected);
    
    Communicator(Communicator const &) = delete; //disable copy-constructor
    Communicator& operator=(Communicator const &other) = delete; //disable assign-operator
    Communicator(Communicator&& other) = delete; //disable move-constructor
    Communicator& operator=(Communicator&& other) = delete; //disable move assign-operator
    

    void sendUserInfo(const UserInfo& userInfo);
    
    /**
     * sends my placed ships to the enemy as guest
     */
    void sendPlacedShipList(const MODEL::CoordinateSystem& myField);
    
    /**
     * sends my placed ships to the enemy as host.
     * We are the one who say who is next turn
     */
    void sendPlacedShipList(const MODEL::CoordinateSystem& myField, bool hostTurn);

private:
    void dataReceived(const QByteArray& data);
    void sendJson(const Command& command, const QJsonValue& json);

    Game& game;
    std::unique_ptr<Connection> conn;
};

} // end NS
#endif // COMMUNICATOR_H
