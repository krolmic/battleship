#ifndef GAME_H
#define GAME_H

namespace MODEL {
    class Connection;
}

namespace MODEL {
class Game
{
public:
    explicit Game();
    virtual ~Game();
    
    Game(Game const &) = delete; //disable copy-constructor
    Game& operator=(Game const &other) = delete; //disable assign-operator
    Game(Game&& other) = delete; //disable move-constructor
    Game& operator=(Game&& other) = delete; //disable move assign-operator
    
    virtual MODEL::Connection& getConnection() = 0;
};

} // NS MODEL
#endif // GAME_H
