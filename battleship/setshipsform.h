#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <coordinatesystem.h>

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
public:
    // TODO: Player Klasse statt QString benutzen, falls die Klasse notwendig
    SetShipsForm(QString *name);

private:
    void createMenu();
    void createPlayerInformationGroupBox();
    void createCoordinateSystemGroupBox();
    void createFormGroupBox();

    void accept();

    QMenuBar *menuBar;
    QMenu *gameMenu;
    QAction *exitAction;
    QAction *deleteShips;

    QGroupBox *playerInformationGroupBox;
    QGroupBox *coordinateSystemGroupBox;
    QDialogButtonBox *buttonBox;

    CoordinateSystem *field;

    QString *playerName;
    QLabel *nameLabel;

    const QSize size;
};

#endif // DIALOG_H
