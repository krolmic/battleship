#ifndef GAMECOORDINATESYSTEM_H
#define GAMECOORDINATESYSTEM_H


#include <qwidget.h>
#include <QGraphicsView>
#include <memory>
#include <coordinatesystem.h>
#include <QLine>

namespace GUI
{
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
