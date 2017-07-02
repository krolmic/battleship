#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include "connection.h"

namespace MODEL {

template <class T>
class A {
  public:
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

class Communicator
{
public:
    Communicator();
    ~Communicator();

    Connection connection;

    void sendPrepareAttack();

private:
    template <class T>
    void encodeJson(A, QString&);
    void decodeJson(QString, A&);
};

} // NS MODEL
#endif // COMMUNICATOR_H
