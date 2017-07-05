#include <QtWidgets>
#include "setshipsform.h"
#include "gameform.h"
#include "player.h"
#include <QString>
#include "common/user_info.h"

GUI::SetShipsForm::SetShipsForm(const UserInfo& me, const UserInfo& enemy, QDialog* parent)
    : QDialog{parent}, meUserInfo{me}, enemyUserInfo{enemy}, size{QSize(450, 680)}
{
    createMenu();
    createPlayerInformationGroupBox();
    createCoordinateSystemGroupBox();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
// 
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(coordinateSystemGroupBox);
    mainLayout->setStretch(0, 1);
    mainLayout->addWidget(playerInformationGroupBox);
    mainLayout->addWidget(enemyPlayerInformationGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
// 
    setWindowTitle(tr("Battleship 0.0.1"));
//     // TODO: scalable, vorerst feste Größe
    resize(size);
    this->setFixedSize(size);

//     QMessageBox mBox;
//     mBox.setWindowTitle( "Message" );
//     // TODO: Genauere Spielanweisungen
//     mBox.setText( "<p align='center'>Welcome " + QString::fromStdString(meUserInfo.getName()) + "!</p>Please place your ships!" );
//     mBox.exec();
}


// GUI::SetShipsForm::SetShipsForm(Player *player)
//     :player(player), size(QSize(450, 680))
// {
//     setAttribute(Qt::WA_DeleteOnClose);
//     createMenu();
//     createPlayerInformationGroupBox();
//     createCoordinateSystemGroupBox();
// 
//     buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//                                      | QDialogButtonBox::Cancel);
// 
//     connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
//     connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
// 
//     QVBoxLayout *mainLayout = new QVBoxLayout;
//     mainLayout->setMenuBar(menuBar);
//     mainLayout->addWidget(coordinateSystemGroupBox);
//     mainLayout->setStretch(0, 1);
//     mainLayout->addWidget(playerInformationGroupBox);
//     mainLayout->addWidget(buttonBox);
//     setLayout(mainLayout);
// 
//     setWindowTitle(tr("Battleship 0.0.1"));
//     // TODO: scalable, vorerst feste Größe
//     //resize(size);
//     this->setFixedSize(size);
// 
//     QMessageBox mBox;
//     mBox.setWindowTitle( "Message" );
//     // TODO: Genauere Spielanweisungen
//     mBox.setText( "<p align='center'>Welcome " + *player->getName() + "!</p>Please place your ships!" );
//     mBox.exec();
// }

void GUI::SetShipsForm::createMenu()
{
    menuBar = new QMenuBar;
    gameMenu = new QMenu(tr("&Game"), this);
    deleteShipsAction = gameMenu->addAction(tr("Delete Ships"));
    exitAction = gameMenu->addAction(tr("E&xit"));
    menuBar->addMenu(gameMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(reject()));
    connect(deleteShipsAction, SIGNAL(triggered()), this, SLOT(deleteShips()));
}

void GUI::SetShipsForm::createPlayerInformationGroupBox()
{
    playerInformationGroupBox = new QGroupBox(tr("Player"), this);
    QVBoxLayout *layout = new QVBoxLayout;
    QString info = "Name:\t\t" + QString::fromStdString(meUserInfo.getName()) + 
                         "\nAge:\t\t" + QString::number(meUserInfo.getAge()) + "\n";
    QLabel *playerInfoLabel = new QLabel(info);
    layout->addWidget(playerInfoLabel);
    playerInformationGroupBox->setLayout(layout);
    
    
    enemyPlayerInformationGroupBox = new QGroupBox(tr("EnemyPlayer"), this);
    QVBoxLayout *enemyLayout = new QVBoxLayout;
    QString EnemyInfo = "Name:\t\t" + QString::fromStdString(enemyUserInfo.getName()) + 
                         "\nAge:\t\t" + QString::number(enemyUserInfo.getAge()) + "\n";
    QLabel *enemyPlayerInfoLabel = new QLabel(EnemyInfo);
    enemyLayout->addWidget(enemyPlayerInfoLabel);
    enemyPlayerInformationGroupBox->setLayout(enemyLayout);
}

// void GUI::SetShipsForm::createPlayerInformationGroupBox()
// {
//     playerInformationGroupBox = new QGroupBox(tr("Player"));
//     QVBoxLayout *layout = new QVBoxLayout;
//     QList<QString> listOfLastOponents = player->getLastOponents();
//     QString lastOponentsNames;
//     for(int i = 0; i < listOfLastOponents.count(); i++)
//     {
//         lastOponentsNames += (i != listOfLastOponents.count()-1) ? listOfLastOponents.at(i) + QString(", ") : listOfLastOponents.at(i) + QString(". ");
//     }
// 
//     QString info = "Name:\t\t" + *player->getName() + "\nAge:\t\t" + QString::number(player->getAge()) + "\n" + *player->getStats() + "\n" + lastOponentsNames;
//     QLabel *playerInfoLabel = new QLabel(info);
//     layout->addWidget(playerInfoLabel);
//     playerInformationGroupBox->setLayout(layout);
// }

void GUI::SetShipsForm::createCoordinateSystemGroupBox()
{
    coordinateSystemGroupBox = new QGroupBox(tr("Ships"));
    QVBoxLayout *layout = new QVBoxLayout;
    field = new GUI::SettingShipsCoordinateSystem{};
    layout->addWidget(field);
    coordinateSystemGroupBox->setLayout(layout);
}

void GUI::SetShipsForm::accept()
{
    // TODO: zum spaeteren Zeitpunkt Ueberpruefung
    // TODO: zum spaeteren Zeitpunkt Uebergabe des Spieler Objekts
    close();
    GameForm *setShipsForm = new GameForm();
    setShipsForm->exec();
}

void GUI::SetShipsForm::deleteShips()
{
    field->clearField();
}
