#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QList>

using namespace std;

class Player
{
public:
    Player(QString* namePlayer, int agePlayer);
    void setName(QString * namePlayer);
    QString* getName();

    void setAge(int age);
    int getAge();

    void setNumberWins(int numberWins);
    int getNumberWins();

    void setNumberGames(int numberGames);
    int getNumberGames();

    void setNumberFailures(int numberFailure);
    int getNumberFailures();

    void setGrade(int grade);
    int getGrade();

    void changeProfile(QString* namePlayer, int age);
    QString* getStats();

    void addLastOponent(QString recentOponents);
    QList<QString> getLastOponents();

private:
    QString* name;
    int age;
    int numberGames = 0;
    int numberWins = 0;
    int numberFailures = 0;
    int grade = 0;
    QList<QString> lastOponents;
};

#endif // PLAYER_H
