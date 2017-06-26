#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game
{

public:
    Game(Player *);

    int numberOfLostShips[2] = {0, 0};
    int numberOfFailures[2] = {0, 0};
    int numberOfFailedHits[2] = {0, 0};

    // setter und getter
    void roundEnd();
    void gameEnd();
    string showStats();

    // Only 2 Players, always
    Player * getPlayers();
    void setPlayers(Player * playerArray);

    int getNumberOfShips();
    void setNumberOfShips(int value);

    int getNumberOfRounds();
    void setNumberOfRounds(int value);

    Player *getBeginner();
    void setBeginner(Player *value);

    Player *getCurrentPlayer();
    void setCurrentPlayer(Player *value);

    Player *getMySelfPlayer();
    void setMySelfPlayer(Player *value);

    Player *getWinner();
    void setWinner(Player *value);

private:
    // Only 2 Players, always
    Player players[2];

    int numberOfShips;
    int numberOfRounds;

    // Players or bool?
    Player * beginner;
    Player * currentPlayer;
    Player * mySelfPlayer;
    Player * winner;
};

#endif // GAME_H
