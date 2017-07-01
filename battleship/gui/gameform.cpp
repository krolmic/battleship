#include "gameform.h"
#include <QtWidgets>
#include "digitalclock.h"
#include "gamecoordinatesystem.h"

GameForm::GameForm()
{
    QGridLayout *mainLayout = new QGridLayout;

    createMenus();
    createCoordinateSystemGroupBoxOwn();
    createCoordinateSystemGroupBoxEnemy();
    createInformationGroupBox();

    mainLayout->addWidget(coordinateSystemGroupBoxOwn,0,0,7,4);
    mainLayout->addWidget(coordinateSystemGroupBoxEnemy,0,4,7,4);
    mainLayout->addWidget(informationGroupBox,8,0,4,8);
    mainLayout->setMenuBar(menuBar);

    setLayout(mainLayout);
    setFixedSize(900,780);

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

void GameForm::createCoordinateSystemGroupBoxOwn()
{
    coordinateSystemGroupBoxOwn = new QGroupBox(tr("Own Field"));
    QVBoxLayout *layout = new QVBoxLayout;
    ownField = new GUI::GameCoordinateSystem;
    layout->addWidget(ownField);
    coordinateSystemGroupBoxOwn->setLayout(layout);
}

void GameForm::createCoordinateSystemGroupBoxEnemy()
{
    coordinateSystemGroupBoxEnemy = new QGroupBox(tr("Enemy Field"));
    QVBoxLayout *layout = new QVBoxLayout;
    enemyField = new GUI::GameCoordinateSystem;
    layout->addWidget(enemyField);
    coordinateSystemGroupBoxEnemy->setLayout(layout);
}

void GameForm::createInformationGroupBox()
{
    informationGroupBox = new QGroupBox("Game");
    QGridLayout *layout = new QGridLayout;

    QLabel *label1 = new QLabel("f(x)=");
    QLabel *label2 = new QLabel("x + ");
    QLineEdit *lineEdit1 = new QLineEdit;
    QLineEdit *lineEdit2 = new QLineEdit;
    QPushButton *checkStraightButton = new QPushButton("Check");
    QLabel *timerLabel = new QLabel("Time left:");
    DigitalClock *digitalClock = new DigitalClock();
    statusBox = new QTextEdit;

    layout->addWidget(label1,0,0,1,1);
    layout->addWidget(lineEdit1,0,1,1,1);
    layout->addWidget(label2,0,2,1,1);
    layout->addWidget(lineEdit2,0,3,1,1);
    layout->addWidget(checkStraightButton,0,4,1,1);
    layout->addWidget(timerLabel,1,0,1,1);
    layout->addWidget(digitalClock,1,1,1,4);
    layout->addWidget(statusBox,2,0,2,6);
    connect(checkStraightButton, SIGNAL(clicked(bool)), this, SLOT(checkStraight()));
    informationGroupBox->setLayout(layout);
}

GameForm::~GameForm()
{
    // delete ui;
}
