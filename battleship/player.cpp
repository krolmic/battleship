#include "player.h"
#include "QString"
#include "QMessageBox"
#include "QList"

using namespace std;

Player::Player(QString* namePlayer, int agePlayer)
{
    name = namePlayer;
    age = agePlayer;
}

void Player::setName(QString* namePlayer)
{
    this->name = namePlayer;
}

QString* Player::getName()
{
    return name;
}

void Player::setAge(int age)
{
    this->age = age;
}

int Player::getAge()
{
    return age;
}

void Player::setNumberWins(int wins)
{
    this->numberWins = wins;
}

int Player::getNumberWins()
{
    return numberWins;
}

void Player::setNumberGames(int numberGames)
{
    this->numberGames = numberGames;
}

int Player::getNumberGames()
{
    return numberGames;
}

void Player::setNumberFailures(int numberFailures)
{
    this->numberFailures = numberFailures;
}

int Player::getNumberFailures()
{
    return numberFailures;
}

void Player::setGrade(int grade)
{
    this->grade = grade;
}

int Player::getGrade()
{
    return grade;
}

void Player::changeProfile(QString* namePlayer, int age)
{
    this->name = namePlayer;
    this->age = age;
}

QString* Player::getStats()
{
    QString failures = QString::number(getNumberFailures());
    QString games = QString::number(getNumberGames());
    QString grade = QString::number(getGrade());
    QString wins = QString::number(getNumberWins());

    QString str = QString("Verloren: ") + failures +  QString("\nGewonnen: ") + wins + QString("\nSpielanzahl: ") + games + QString("\nNiveau: ") + grade + "";
    QString *stats = new QString(str);
    return stats;
}

void Player::addLastOponent(QString lastOponent)
{
    lastOponents << lastOponent;
}

QList<QString> Player::getLastOponents()
{
    return lastOponents;
}
