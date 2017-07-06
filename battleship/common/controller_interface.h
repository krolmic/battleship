#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H

class QString;
class QPoint;
class ModelInterface;

/// The base class that defines the controller interface
class ControllerInterface //https://stackoverflow.com/questions/14323595/best-way-to-declare-an-interface-in-c11
{
public:
    virtual ~ControllerInterface () { }
    
    virtual bool placeShip(const QPoint& p1, const QPoint p2) = 0;
    
    /**
     * begin new game as host over the network. But first wat for guest  to join.
     */
    virtual void startNewGameAsHost(const QString& playerName, const QString& age) = 0;
    
    /**
     * connect to a host as a guest over the network
     */
    virtual void startNewGameAsGuest(
        const QString& address, 
        const QString& port, 
        const QString& playerName, 
        const QString& age) = 0;

};

#endif // CONTROLLERINTERFACE_H
