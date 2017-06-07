#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QDataStream>
#include <coordinatesystem.h>
#include "player.h"

class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QTcpSocket;
class QNetworkSession;

class SetShipsForm : public QDialog
{
public:
    // TODO: Player Klasse statt QString benutzen, falls die Klasse notwendig
    SetShipsForm(Player *player);

private:
    void createMenu();
    void createPlayerInformationGroupBox();
    void createCoordinateSystemGroupBox();
    void createFormGroupBox();
    void connectToServer();
    void accept();
    void read();
    QMenuBar *menuBar;
    QMenu *gameMenu;
    QAction *exitAction;
    QAction *deleteShips;
    QTcpSocket *tcpSocket;
    QDataStream in;
    QString testString;

    QNetworkSession *networkSession;
    QGroupBox *playerInformationGroupBox;
    QGroupBox *coordinateSystemGroupBox;
    QDialogButtonBox *buttonBox;

    CoordinateSystem *field;

    Player *player;
    QLabel *nameLabel;

    const QSize size;
};

#endif // DIALOG_H
