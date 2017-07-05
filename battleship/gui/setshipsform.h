#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "coordinatesystem.h"
#include "settingshipscoordinatesystem.h"
#include "player.h"
#include "common/user_info.h"

class QAction;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;

namespace GUI {
    
class BattleshipView;


/// A simple class that defines graphical interface of the form in which players are able to set ships
class SetShipsForm : public QDialog
{
    Q_OBJECT

public:
    // TODO: Player Klasse statt QString benutzen, falls die Klasse notwendig
    SetShipsForm(const UserInfo& me, const UserInfo& enemy, QDialog* parent = nullptr);

private:
    void createMenu();
    void createPlayerInformationGroupBox();
    void createCoordinateSystemGroupBox();
    void createFormGroupBox();

    void accept();

    UserInfo meUserInfo;
    UserInfo enemyUserInfo;
    
    QMenuBar *menuBar;
    QMenu *gameMenu;
    QAction *exitAction;
    QAction *deleteShipsAction;

    QGroupBox *playerInformationGroupBox;
    QGroupBox *enemyPlayerInformationGroupBox;
    QGroupBox *coordinateSystemGroupBox;
    QDialogButtonBox *buttonBox;

    GUI::SettingShipsCoordinateSystem *field;

//     Player *player;
    QLabel *nameLabel;

    const QSize size;

private slots:

    void deleteShips();
};

} //end NS
#endif // DIALOG_H
