#include <QApplication>
#include <QtCore>
#include <stdlib.h>
#include "servergui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Servergui gui;
    gui.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return app.exec();
}
