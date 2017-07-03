#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include "connection.h"
#include "gui/player.h"

namespace MODEL {
/** Jede Klasse, dessen Objekte in JSON-Format über das Netzwerk verschickt werden,
 * implementiert die Methoden read(const QJsonObject &json) und write(QJsonObject &json), somit
 * werden die decode- und encode Methoden der Klasse Communicator uebersichtlicher.
**/
class Communicator
{
public:
    /// Dient zur Kennzeichnung der Befehle
    enum ObjectType
    {
        prepareAttack = 0,
        attackResult = 0,
        player = 1
    };

    Communicator();
    ~Communicator();

    /// Versendet die Befehle
    Connection connection;

    void readData();
    void sendData();

private:
    /// Uebersetzen der Klassen in JSON und andersherum
    void encodePlayerToJsonString(Player, QString&);
    void decodeJsonStringToPlayer(QString, Player&);
    void encodeAttackToJsonString(Player, QString&);
    void decodeJsonStringToAttack(QString, Player&);

    /// Erstellt ein
    QJsonObject createJsonObjectFromString(const QString& in);

} // NS MODEL
#endif // COMMUNICATOR_H
