#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QDialog>
#include <QTextEdit>
#include <QGridLayout>
#include "coordinatesystem.h"
#include "gamecoordinatesystem.h"

class QAction;
class QMenu;
class QMenuBar;
class QGroupBox;
class QLabel;
class QLineEdit;
class QTableWidget;

// namespace Ui {
// class Dialog;
// }
/// A simple class that defines graphical interface of the form in which players are able to attack, recieve attack, etc.
class GameForm : public QDialog
{
    Q_OBJECT

public:
    GameForm(const std::deque<MODEL::Ship>& me, const std::deque<MODEL::Ship>& enemy, bool myTurn, QDialog* parent = nullptr);
    ~GameForm();
    QString statusBoxText = "";

private:
    void createMenus();
    void createCoordinateSystemGroupBoxOwn(const std::deque<MODEL::Ship>& me);
    void createCoordinateSystemGroupBoxEnemy();
    void createInformationGroupBox();

    // enum { NumGridRows = 3, NumButtons = 4 };

    GUI::GameCoordinateSystem *ownField;
    GUI::GameCoordinateSystem *enemyField;
    QGroupBox* coordinateSystemGroupBoxOwn;
    QGroupBox* coordinateSystemGroupBoxEnemy;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *resetAction;
    QAction *exitAction;
    QAction *versionAction;
    QGroupBox *gridGroupBoxEnemy;
    QGroupBox *gridGroupBoxOwn;
    QGroupBox *informationGroupBox;
    int heightScreen;
    int widthScreen;
    QTextEdit *statusBox;
    // QLabel *labels[NumGridRows];
    // QLineEdit *lineEdits[NumGridRows];

    GUI::GameCoordinateSystem *enemyField1;
    GUI::GameCoordinateSystem *enemyField2;
    QTableWidget *statisticTable;
    GUI::GameCoordinateSystem *ownField1;

private slots:
    void openVersion();
    void resetOwnField();
    void checkStraight();
};

#endif // GAMEFORM_H




