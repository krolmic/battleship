#include <QtWidgets>
#include "setshipsform.h"
#include "gameform.h"
#include "player.h"
#include <QString>

SetShipsForm::SetShipsForm(Player *player)
    :player(player), size(QSize(450, 660))
{

    createMenu();
    createPlayerInformationGroupBox();
    createCoordinateSystemGroupBox();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(coordinateSystemGroupBox);
    mainLayout->setStretch(0, 1);
    mainLayout->addWidget(playerInformationGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Battleship 0.0.1"));
    // TODO: scalable, vorerst feste Größe
    //resize(size);
    this->setFixedSize(size);

    QMessageBox mBox;
    mBox.setWindowTitle( "Message" );
    // TODO: Genauere Spielanweisungen
    mBox.setText( "<p align='center'>Welcome " + *player->getName() + "!</p>Please place your ships!" );
    mBox.exec();
}

void SetShipsForm::createMenu()
{
    menuBar = new QMenuBar;
    gameMenu = new QMenu(tr("&Game"), this);
    deleteShipsAction = gameMenu->addAction(tr("Delete Ships"));
    exitAction = gameMenu->addAction(tr("E&xit"));
    menuBar->addMenu(gameMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(reject()));
    connect(deleteShipsAction, SIGNAL(triggered()), this, SLOT(deleteShips()));
}

void SetShipsForm::createPlayerInformationGroupBox()
{
    playerInformationGroupBox = new QGroupBox(tr("Player"));
    QVBoxLayout *layout = new QVBoxLayout;
    QList<QString> listOfLastOponents = player->getLastOponents();
    QString lastOponentsNames;
    for(int i = 0; i < listOfLastOponents.count(); i++)
    {
        lastOponentsNames += (i != listOfLastOponents.count()-1) ? listOfLastOponents.at(i) + QString(", ") : listOfLastOponents.at(i) + QString(". ");
    }

    QString info = "Name:\t\t" + *player->getName() + "\nAge:\t\t" + QString::number(player->getAge()) + "\n" + *player->getStats() + "\n" + lastOponentsNames;
    QLabel *playerInfoLabel = new QLabel(info);
    layout->addWidget(playerInfoLabel);
    playerInformationGroupBox->setLayout(layout);
}

void SetShipsForm::createCoordinateSystemGroupBox()
{
    coordinateSystemGroupBox = new QGroupBox(tr("Ships"));
    QVBoxLayout *layout = new QVBoxLayout;
    field = new GUI::SettingShipsCoordinateSystem;
    layout->addWidget(field);
    coordinateSystemGroupBox->setLayout(layout);
}

void SetShipsForm::accept()
{
    // TODO: zum spaeteren Zeitpunkt Ueberpruefung
    // TODO: zum spaeteren Zeitpunk Uebergabe des Spieler Objekts
    close();
    GameForm *setShipsForm = new GameForm();
    setShipsForm->exec();
}

void SetShipsForm::deleteShips()
{
    field->clearField();
}
