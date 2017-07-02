#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H
#include <QLCDNumber>

class DigitalClock : public QLCDNumber
{
    Q_OBJECT
public:
    DigitalClock(int stopAfterMs = 120000, int beginMin = 2, int beginSec = 0);

private:
    QTimer* containerTimer;
    QTimer* timer;
    QTime*  timeValue;
    int stopAfterMs;
    int beginMin;
    int beginSec;

private slots:
    void showTime();
    void stopTime();
};

#endif // DIGITALCLOCK_H
