#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <memory>
#include "connection.h"

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
    
private:
    void dataReceived(const QByteArray& data);
    
    
    Game& game;
    std::unique_ptr<Connection> conn;
};

} // end NS
#endif // COMMUNICATOR_H
