#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <memory>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "connection.h"
#include "gui/player.h"

namespace MODEL {

class Game;

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
    
    enum objectType
    {
        result,
        attack,
        player,
        timeout
    };
private:
    /**
     * Creates model objects from  json-formatted data
     *
     * @param data recieved in json
     */
    void recieveData(const QByteArray& data);
    /// Creates json object from @param p
    void sendPlayer(Player& p);
    
    Game& game;
    std::unique_ptr<Connection> conn;
};

} // end NS
#endif // COMMUNICATOR_H
