#ifndef CONNECTION_H
#define CONNECTION_H
 
namespace MODEL {
class Connection
{

public:
    explicit Connection();
    virtual ~Connection();
    Connection(Connection const &) = delete; //disable copy-constructor
    Connection& operator=(Connection const &other) = delete; //disable assign-operator
    Connection(Connection&& other) = delete; //disable move-constructor
    Connection& operator=(Connection&& other) = delete; //disable move assign-operator
    
};

} // NS MODEL
#endif // CONNECTION_H
