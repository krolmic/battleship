#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

#include <string>

class ControllerInterface //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~ControllerInterface () { }
    
    
    /**
     * begin new game as host over the network. But first wat for guest  to join.
     */
    virtual void startNewGameAsHost(const std::string& playerName, int age) = 0;
    
    /**
     * connect to a host as a guest over the network
     */
    virtual void startNewGameAsGuest(const std::string& address, int port, const std::string& playerName, int age) = 0;

};

#endif // CONTROLLERINTERFACE_H
