#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "coordinatesystem.h"
#include "settingshipscoordinatesystem.h"
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



class SetShipsForm : public QDialog
{
    Q_OBJECT

public:
    // TODO: Player Klasse statt QString benutzen, falls die Klasse notwendig
    SetShipsForm(Player *player);

private:
    void createMenu();
    void createPlayerInformationGroupBox();
    void createCoordinateSystemGroupBox();
    void createFormGroupBox();

    void accept();

    QMenuBar *menuBar;
    QMenu *gameMenu;
    QAction *exitAction;
    QAction *deleteShipsAction;

    QGroupBox *playerInformationGroupBox;
    QGroupBox *coordinateSystemGroupBox;
    QDialogButtonBox *buttonBox;

    GUI::SettingShipsCoordinateSystem *field;

    Player *player;
    QLabel *nameLabel;

    const QSize size;

private slots:

    void deleteShips();
};

#endif // DIALOG_H
