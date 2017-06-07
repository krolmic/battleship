#include <QtWidgets>
#include "setshipsform.h"
#include "gameform.h"
#include "player.h"
#include <QString>
#include <QtNetwork>

SetShipsForm::SetShipsForm(Player *player)
    :player(player)
    ,size(QSize(500, 700))
    ,tcpSocket(new QTcpSocket(this))
    ,networkSession(Q_NULLPTR)
{
    createMenu();
    createPlayerInformationGroupBox();
    createCoordinateSystemGroupBox();

    //! [1]
    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    //! [1]
    connectToServer();

    connect(tcpSocket, &QIODevice::readyRead, this, &SetShipsForm::read);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(coordinateSystemGroupBox);
    mainLayout->addWidget(playerInformationGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Battleship 0.0.1"));
    resize(size);
}

void SetShipsForm::createMenu()
{
    menuBar = new QMenuBar;
    gameMenu = new QMenu(tr("&Game"), this);
    deleteShips = gameMenu->addAction(tr("Delete Ships"));
    exitAction = gameMenu->addAction(tr("E&xit"));
    menuBar->addMenu(gameMenu);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
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

    QString info = player->getName() + QString("\n") + QString(QString::number(player->getAge())) + QString("\n") + player->getStats() + QString("\n") + QString(lastOponentsNames);

    QString* playerInfo = new QString(info);
    QLabel *playerInfoLabel = new QLabel(playerInfo->toStdString().c_str());
    layout->addWidget(playerInfoLabel);
    playerInformationGroupBox->setLayout(layout);
}

void SetShipsForm::createCoordinateSystemGroupBox()
{
    coordinateSystemGroupBox = new QGroupBox(tr("Ships"));
    QVBoxLayout *layout = new QVBoxLayout;
    field = new CoordinateSystem;
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

void SetShipsForm::connectToServer()
{
    tcpSocket->abort();
    tcpSocket->connectToHost("127.0.0.1",44452);
}

void SetShipsForm::read()
{
    in.startTransaction();

    QString testString;
    in >> testString;

    if (!in.commitTransaction())
        return;
    qDebug()<<testString;
}
