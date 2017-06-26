#include "game.h"
#include "player.h"

Game::Game(Player * playerArray)
{
    setPlayers(playerArray);
}

void Game::roundEnd()
{
    // Was gehört hier drin?
}

void Game::gameEnd()
{
    // Was gehört hier drin?
}

string Game::showStats()
{
    return "Number of Rounds: " + std::to_string(getNumberOfRounds())
            + ".\nPlayer 1:\nNumber of lost ships: " + std::to_string(numberOfLostShips[0]) + "\nNumber of failures: "
            +  std::to_string(numberOfFailures[0]) + "\nNumber of failed hits: "+ std::to_string(numberOfFailedHits[0]) + "."
            + ".\nPlayer 2:\nNumber of lost ships: " + std::to_string(numberOfLostShips[1]) + "\nNumber of failures: "
            +  std::to_string(numberOfFailures[1]) + "\nNumber of failed hits: " + std::to_string(numberOfFailedHits[1]) + ".";
}

void Game::setPlayers(Player * playerArray)
{
    for (int i = 0; i < 2; i++)
    {
        players[i] = playerArray[i];
    }
}

Player* Game::getPlayers()
{
    return players;
}

int Game::getNumberOfShips()
{
    return numberOfShips;
}

void Game::setNumberOfShips(int value)
{
    numberOfShips = value;
}

int Game::getNumberOfRounds()
{
    return numberOfRounds;
}

void Game::setNumberOfRounds(int value)
{
    numberOfRounds = value;
}

Player *Game::getBeginner()
{
    return beginner;
}

void Game::setBeginner(Player *value)
{
    beginner = value;
}

Player *Game::getCurrentPlayer()
{
    return currentPlayer;
}

void Game::setCurrentPlayer(Player *value)
{
    currentPlayer = value;
}

Player *Game::getMySelfPlayer()
{
    return mySelfPlayer;
}

void Game::setMySelfPlayer(Player *value)
{
    mySelfPlayer = value;
}

Player *Game::getWinner()
{
    return winner;
}

void Game::setWinner(Player *value)
{
    winner = value;
}
