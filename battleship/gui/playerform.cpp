#include <QtWidgets>
#include "playerform.h"
#include "setshipsform.h"
#include "application.h"

PlayerForm::PlayerForm(Application& app, QWidget* parent)
    : QDialog(parent), app{app}
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
    connect(directConnBtn, &QPushButton::clicked, this, &PlayerForm::connectToHost);

    // Setzen des Layouts
    setLayout(mainLayout);
    setWindowTitle(tr("Player Form"));
    setAttribute(Qt::WA_DeleteOnClose); //clean up memory, since it's not needed anymore
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

// void PlayerForm::closeEvent(QCloseEvent*)
// {
//     qDebug() << "closeEvent";
//     deleteLater();
// }


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
        SetShipsForm *setShipsForm = new SetShipsForm(player);
        setShipsForm->show(); //with exec() setAttribute(Qt::WA_DeleteOnClose) doesn't work
        close();
    }
    qDebug() << "END of void PlayerForm::accept()";
}

void PlayerForm::hostGame()
{
    app.startNewGameAsHost();
}

void PlayerForm::connectToHost()
{
    app.startNewGameAsGuest("localhost", 3570);
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
