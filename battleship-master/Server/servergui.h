#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QWidget>
#include "server.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Servergui : public QWidget
{
    Q_OBJECT

public:
    Servergui(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    QPushButton *resultButton;
    Server server;
};

#endif
