#ifndef GAME_H
#define GAME_H

#include "communicator.h"

class BattleshipObserver;

namespace MODEL {
class Game
{
public:
//     explicit Game();
    explicit Game(std::vector<std::reference_wrapper<BattleshipObserver>>& observerList);
    explicit Game(const std::string& address, int port,
        std::vector<std::reference_wrapper<BattleshipObserver>>& observerList
    );
    
    virtual ~Game();
    
    Game(Game const &) = delete; //disable copy-constructor
    Game& operator=(Game const &other) = delete; //disable assign-operator
    Game(Game&& other) = delete; //disable move-constructor
    Game& operator=(Game&& other) = delete; //disable move assign-operator
    
    
    
protected:
    virtual void socketConnected() = 0;
    std::vector<std::reference_wrapper<BattleshipObserver>>& observerList;
    
    
private:
    Communicator com;
};

} // NS MODEL
#endif // GAME_H
