#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QDialog>
#include <coordinatesystem.h>
#include <gamecoordinatesystem.h>
#include <QTextEdit>

class QAction;
class QMenu;
class QMenuBar;
class QGroupBox;
class QLabel;
class QLineEdit;
class QTableWidget;

namespace Ui {
class Dialog;
}

class GameForm : public QDialog
{
    Q_OBJECT

public:
    GameForm();
    ~GameForm();
    QString statusBoxText;

private:
    //Ui::Dialog *ui;
        void createMenus();
        void createGridGroupBoxLeft();
        void createGridGroupBoxRight();

        // enum { NumGridRows = 3, NumButtons = 4 };

        QMenuBar *menuBar;
        QMenu *fileMenu;
        QMenu *helpMenu;
        QAction *resetAction;
        QAction *exitAction;
        QAction *versionAction;
        QGroupBox *gridGroupBoxEnemy;
        QGroupBox *gridGroupBoxOwn;
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



