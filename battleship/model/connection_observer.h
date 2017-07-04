#ifndef CONNECTIONOBSERVER_H
#define CONNECTIONOBSERVER_H

class ConnectionObserver
{
public:
    virtual ~ConnectionObserver () { }
    
    /**
     * Event when peer has successfully connected
     */
    virtual void connectionEstablished() = 0;
};

#endif // CONNECTIONOBSERVER_H
