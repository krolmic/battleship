#include "digitalclock.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>

DigitalClock::DigitalClock(int stopAfterMs, int beginMin, int beginSec)
{
    this->stopAfterMs = stopAfterMs;
    this->beginMin = beginMin;
    this->beginSec = beginSec;
    setSegmentStyle(Filled);

    containerTimer = new QTimer(this);
    connect(containerTimer, SIGNAL(timeout()), this, SLOT(stopTime()));
    containerTimer->start(stopAfterMs);

    timer = new QTimer(this);
    timeValue = new QTime(0,beginMin,beginSec);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    showTime();
    timer->start(1000);

    setWindowTitle(tr("Digital Clock"));
    resize(250, 150);
}

void DigitalClock::showTime()
{
    timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
    display(timeValue->toString());
}

void DigitalClock::stopTime()
{
    timer->stop();
    containerTimer->stop();

    QMessageBox msgBox;
    msgBox.setText("Die Zeit ist abgelaufen");
    msgBox.setWindowTitle("Warnung");
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Close);
    msgBox.exec();
}
