#include "communicator.h"

using namespace MODEL;

Communicator::Communicator()
{
}

Communicator::~Communicator()
{
}

void Communicator::encodeJson(T obj, QString& str)
{
    QJsonObject object;
    obj.write(object);
    QJsonDocument doc(object);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    str = data;
}

void MODEL::Communicator::decodeJson(QString str, T& obj)
{

}
