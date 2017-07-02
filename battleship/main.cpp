#include <QApplication>
// #include "gui/playerform.h"
// #include "gui/gameform.h"
#include "model/battleship_model.h"
#include "battleship_controller.h"

int main(int argc, char *argv[])
{
    QApplication guiApp(argc, argv);
    
    MODEL::BattleshipModel model{};
    BattleshipController ctrl{model};
    
//     auto* playerForm = new PlayerForm{app};
//     playerForm->show();
// 
    return guiApp.exec();
} // Ende main
