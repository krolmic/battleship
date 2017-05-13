#include <QtWidgets>
#include "playerform.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PlayerForm playerForm;
    playerForm.show();

    return app.exec();
} // Ende main
