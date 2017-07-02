#include "application.h"
// #include <QtWidgets>
#include <QApplication>
#include "gui/playerform.h"
#include "gui/gameform.h"

int main(int argc, char *argv[])
{
    QApplication guiApp(argc, argv);
    Application app{};
    
    auto* playerForm = new PlayerForm{app};
    playerForm->show();

    return guiApp.exec();
} // Ende main
