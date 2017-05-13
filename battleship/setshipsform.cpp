#include <QtWidgets>
#include "setshipsform.h"

SetShipsForm::SetShipsForm(QString *name)
    :playerName(name), size(QSize(500, 700))
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
    // Unschoen
    QLabel *nameLabel = new QLabel(tr(playerName->toStdString().c_str()));
    layout->addWidget(nameLabel);
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

