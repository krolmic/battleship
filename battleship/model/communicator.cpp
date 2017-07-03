#include "communicator.h"

using namespace MODEL;

Communicator::Communicator()
{
}

Communicator::~Communicator()
{
}

void Communicator::encodePlayerToJsonString(Player obj, QString& str)
{
    QJsonObject object;
    obj.write(object);
    QJsonDocument doc(object);
    QByteArray data = doc.toJson(QJsonDocument::Compact);
    str = data;
}

void Communicator::decodeJsonStringToPlayer(QString str, Player& obj)
{
    QJsonObject obj = createJsonObjectFromString(str);
    obj.read(obj);
}

QJsonObject Communicator::createJsonObjectFromString(const QString& in)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
    // hat es geklappt?
    if(!doc.isNull())
    {
        if(doc.isObject())
            obj = doc.object();
        else
            qDebug() << "QJsonDocument enthaelt mehrere Objekte" << endl;
    }
    else
        qDebug() << "JSON-Format nicht erkannt" << in << endl;
    return obj;
}

void Communicator::sendData()
{
    // encode...
    // connection->send(encodedData)
}

void Communicator:recieveData()
{
    // decode...
    // switch-case
}
