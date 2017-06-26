#include <QtWidgets>
#include "gui/playerform.h"
#include "gui/gameform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PlayerForm playerForm;
    playerForm.show();

    //GameForm gameForm;
    //gameForm.show();

    return app.exec();
} // Ende main
