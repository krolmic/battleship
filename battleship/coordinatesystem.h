#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include <qwidget.h>


class CoordinateSystem : public QWidget
{
public:
    CoordinateSystem();
    ~CoordinateSystem();
    void paintEvent(QPaintEvent * event);
};

#endif // COORDINATESYSTEM_H
