#include <QtWidgets>
#include "playerform.h"
#include "setshipsform.h"


PlayerForm::PlayerForm()
{
    // "Name:"
    createPlayerInputFieldsGroup();

    // Definition der Ok und Cancel Buttons
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    // Layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(buttonBox);
    
    // add connection possibilities
    mainLayout->addWidget(createPlayerConnectionSelectGroup());
    connect(hostGameBtn, &QPushButton::clicked, this, &PlayerForm::hostGame);
    connect(directConnBtn, &QPushButton::clicked, this, &PlayerForm::connectDirect);
//     mainLayout->addWidget(hostGameBtn);

    // Setzen des Layouts
    setLayout(mainLayout);
    setWindowTitle(tr("Player Form"));
}

void PlayerForm::createPlayerInputFieldsGroup()
{
    // Layout
    horizontalGroupBox = new QGroupBox(tr("Enter your data"));
    QHBoxLayout *layout = new QHBoxLayout;

    // Inputfelder
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;

    QLabel *ageLabel = new QLabel(tr("Age:"));
    ageLine = new QLineEdit;

    layout->addWidget(nameLabel);
    layout->addWidget(nameLine);
    layout->addWidget(ageLabel);
    layout->addWidget(ageLine);

    // Setzen des Layouts
    horizontalGroupBox->setLayout(layout);
}

// Implementation der virtuellen Methode QDialog::accept()
void PlayerForm::accept()
{
    // Der Name darf nicht leer sein
    if(nameLine->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Sorry, an error occurred.");
        msgBox.setInformativeText("Please enter your name.");
        msgBox.exec();
    }
    else
    {
        // GUI für Schiffe Setzen anzeigen
        // Player Form schliessen
        int ageNumber = (ageLine->text()).toInt();

        //QString* name = new QString(nameLine->text());
        player = new Player(new QString(nameLine->text()), ageNumber);
        close();
        SetShipsForm *setShipsForm = new SetShipsForm(player);
        setShipsForm->exec();
    }
}

QGroupBox* PlayerForm::createPlayerConnectionSelectGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("How do you want connect?"));
    
    hostGameBtn = new QPushButton(tr("Host game"), this);
    directConnBtn = new QPushButton(tr("Connect to host"), this);
    
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(hostGameBtn);
    layout->addWidget(directConnBtn);
    
    groupBox->setLayout(layout);
    return groupBox;
}

void PlayerForm::connectDirect()
{
    qDebug() << "lets do direct connect";
}

void PlayerForm::hostGame()
{
    qDebug() << "lets host a game";
}




