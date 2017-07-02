#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <memory>
#include "model/game.h"

class Application
{
public:
    explicit Application();
    Application(Application const &) = delete; //disable copy-constructor
    Application& operator=(Application const &other) = delete; //disable assign-operator
    Application(Application&& other) = delete; //disable move-constructor
    Application& operator=(Application&& other) = delete; //disable move assign-operator
    
    void startNewGameAsHost();
    void startNewGameAsGuest(const std::string& address, int port);
    
private:
    std::unique_ptr<MODEL::Game> game = nullptr;
    
};

#endif // APPLICATION_H
