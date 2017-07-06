#ifndef SETTINGSHIPSCOORDINATESYSTEM_H
#define SETTINGSHIPSCOORDINATESYSTEM_H
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>
#include "coordinatesystem.h"

class ControllerInterface;

namespace GUI
{
/// A simple class that inherits from CoordinateSystem and implements mouse events for setting ships
class SettingShipsCoordinateSystem : public CoordinateSystem
{
public:
    using CoordinateSystem::CoordinateSystem;
    SettingShipsCoordinateSystem(ControllerInterface& ctrl);
    ~SettingShipsCoordinateSystem();

    void fillPointsList();
    QPoint getNextPointFromVector(int, int, std::vector<QPoint>&);
    void clearInvalidPossiblePoints();

    void nextShipPoint(int&, int&, int, int);
    bool isValidDistance(int, int, int, int);
    bool isValidPlacement(int, int, int, int);

    // Aktualisieren des Koordinatensystems
    void clearField();

    // Events
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);

private:
    // TODO: Namen verbessern
    ControllerInterface& ctrl;
    bool forbiddenToPlaceShips{false};
    std::vector<QPoint> possible_points; // Moegliche Punkte bei mouseReleaseEvent
};
}

#endif // SETTINGSHIPSCOORDINATESYSTEM_H
