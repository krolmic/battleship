#include "game.h"
#include <QDebug>

// MODEL::Game::Game()
// {
// 
// }

MODEL::Game::Game(std::function<void ()> callbackOnConnected)
    : com{*this, std::bind(&MODEL::Game::socketConnected, this)}
{
}

void MODEL::Game::socketConnected()
{
    qDebug() << "MODEL::Game::socketConnected()";
}



MODEL::Game::~Game()
{
    qDebug() << "~Game dtor";
}

