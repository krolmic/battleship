#ifndef GAME_H
#define GAME_H

#include "communicator.h"

namespace MODEL {
class Game
{
public:
//     explicit Game();
    explicit Game(std::function<void()> callbackOnConnected);
    
    virtual ~Game();
    
    Game(Game const &) = delete; //disable copy-constructor
    Game& operator=(Game const &other) = delete; //disable assign-operator
    Game(Game&& other) = delete; //disable move-constructor
    Game& operator=(Game&& other) = delete; //disable move assign-operator
    
protected:
    void socketConnected();
    
    
private:
    Communicator com;
};

} // NS MODEL
#endif // GAME_H
