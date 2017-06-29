#include "gameform.h"
#include <QtWidgets>
#include "digitalclock.h"
#include "gamecoordinatesystem.h"

GameForm::GameForm()
{
    setStyleSheet("QStatusBar{background: white; margin-bottom: 0px;} Dialog {background: LightBlue; }");

    createMenus();
    createGridGroupBoxLeft();
    createGridGroupBoxRight();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setMenuBar(menuBar);

    QHBoxLayout *subLayout = new QHBoxLayout;


    subLayout->addWidget(gridGroupBoxEnemy);
    subLayout->addWidget(gridGroupBoxOwn);

    mainLayout->addLayout(subLayout, 0, 0, 20,1);

    setLayout(mainLayout);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    heightScreen = screenGeometry.height() * 0.85;
    widthScreen = screenGeometry.width() * 0.85;

    setFixedSize(900,800);
    setWindowTitle(tr("Battleship 0.0.1"));
}

void GameForm::createMenus()
{
    menuBar = new QMenuBar;

    fileMenu = new QMenu("Game", this);
    resetAction = fileMenu->addAction("&Reset");
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction("E&xit");
    menuBar->addMenu(fileMenu);

    helpMenu = new QMenu("Help", this);
    versionAction = helpMenu->addAction("&Version");
    menuBar->addMenu(helpMenu);

    connect(resetAction, SIGNAL(triggered()), this, SLOT(resetOwnField()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(versionAction, SIGNAL(triggered()), this, SLOT(openVersion()));
}

void GameForm::resetOwnField()
{

}

void GameForm::openVersion()
{
    QMessageBox msgBox;
    msgBox.setText("Version 0.0.1");
    msgBox.setWindowTitle("Battleship 0.0.1");
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();
}

void GameForm::checkStraight()
{
    QMessageBox msgBox;
    msgBox.setText("Straight Result");
    msgBox.setWindowTitle("I am a MessageBox");
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();
}

void GameForm::createGridGroupBoxLeft()
{
    gridGroupBoxEnemy = new QGroupBox("Enemy Field");
    QGridLayout *layoutLeft = new QGridLayout;

    enemyField1 = new GUI::GameCoordinateSystem;
    //enemyField1->setDisabled(true);
    layoutLeft->addWidget(enemyField1, 0, 0, 6, 4);

    // Die ganzen Daten, die weiterverwendet werden, in eine andere Klasse bewegen.
    QGridLayout *straightFunctionLayout = new QGridLayout;

    QLabel *label1 = new QLabel("f(x)=");
    QLabel *label2 = new QLabel("x + ");
    QLineEdit *lineEdit1 = new QLineEdit;
    QLineEdit *lineEdit2 = new QLineEdit;
    QPushButton *checkStraightButton = new QPushButton("Check");
    straightFunctionLayout->addWidget(label1, 0, 0, 1, 1);
    straightFunctionLayout->addWidget(lineEdit1, 0, 1, 1, 1);
    straightFunctionLayout->addWidget(label2, 0, 2, 1, 1);
    straightFunctionLayout->addWidget(lineEdit2, 0, 3, 1, 1);
    straightFunctionLayout->addWidget(checkStraightButton, 0, 4, 1, 1);
    connect(checkStraightButton, SIGNAL(clicked(bool)), this, SLOT(checkStraight()));
    // Der Button sollte was tun
    DigitalClock *digitalClock = new DigitalClock();
    straightFunctionLayout->addWidget(digitalClock, 1, 0, 2, 2);
    layoutLeft->addLayout(straightFunctionLayout, 6, 0, 1, 4);

    statusBox = new QTextEdit(statusBoxText, this);
    layoutLeft->addWidget(statusBox, 7, 0, 2, 4);

    gridGroupBoxEnemy->setLayout(layoutLeft);
}

void GameForm::createGridGroupBoxRight()
{
    gridGroupBoxOwn = new QGroupBox("Own Field");
    QGridLayout *layoutRight = new QGridLayout;

    ownField1 = new GUI::GameCoordinateSystem;
    layoutRight->addWidget(ownField1, 0, 0, 4, 4);


    statisticTable = new QTableWidget(3,2, this);
    QTableWidgetItem *restShipsEnemy = new QTableWidgetItem("5");
    QTableWidgetItem *resShipsOwn = new QTableWidgetItem("4");
    QTableWidgetItem *straightErrorsEnemy = new QTableWidgetItem("8");
    QTableWidgetItem *straightErrorsOwn = new QTableWidgetItem("7");
    QTableWidgetItem *wrongShotEnemy = new QTableWidgetItem("6");
    QTableWidgetItem *wrongShotOwn = new QTableWidgetItem("4");
    statisticTable->setItem(0,0,restShipsEnemy);
    statisticTable->setItem(0,1,resShipsOwn);
    statisticTable->setItem(1,0,straightErrorsEnemy);
    statisticTable->setItem(1,1,straightErrorsOwn);
    statisticTable->setItem(2,0,wrongShotEnemy);
    statisticTable->setItem(2,1,wrongShotOwn);

    QStringList rowHeaderList;
    rowHeaderList << "Ramaining ships" << "Equation errors" << "Miss";
    QStringList colHeaderList;
    colHeaderList << "Enemy" << "Own";

    statisticTable->setHorizontalHeaderLabels(colHeaderList);
    statisticTable->setVerticalHeaderLabels(rowHeaderList);
    statisticTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    statisticTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    layoutRight->addWidget(statisticTable, 4, 0, 2, 4);

    // TODO: Exit-Button unterhalb Enemy und Own Field
    QPushButton *giveUpButton = new QPushButton("Exit");
    connect(giveUpButton, SIGNAL(clicked(bool)), this, SLOT(close()));
    layoutRight->addWidget(giveUpButton, 6, 3, 1, 1);


    gridGroupBoxOwn->setLayout(layoutRight);
}

GameForm::~GameForm()
{
    // delete ui;
}
