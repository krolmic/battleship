#ifndef GAMECOORDINATESYSTEM_H
#define GAMECOORDINATESYSTEM_H


#include "coordinatesystem.h"
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>
#include <QLine>

namespace GUI
{
/// A simple class that inherits from CoordinateSystem and implements mouse events for starting attack
class GameCoordinateSystem : public CoordinateSystem
{
public:
    using CoordinateSystem::CoordinateSystem;
    ~GameCoordinateSystem();

    void paintShots();
    void clearField();

    // Events
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);



};
}

#endif // GAMECOORDINATESYSTEM_H
