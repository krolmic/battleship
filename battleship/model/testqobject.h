#ifndef TESTQOBJECT_H
#define TESTQOBJECT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

namespace MODEL {
class TestQObject : public QObject
{
    Q_OBJECT
public:
    explicit TestQObject();
};

}
#endif // TESTQOBJECT_H
