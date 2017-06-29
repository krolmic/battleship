#ifndef SETTINGSHIPSCOORDINATESYSTEM_H
#define SETTINGSHIPSCOORDINATESYSTEM_H
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>
#include "coordinatesystem.h"

namespace GUI
{
class SettingShipsCoordinateSystem : public CoordinateSystem
{
public:
    using CoordinateSystem::CoordinateSystem;
    ~SettingShipsCoordinateSystem();

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
    std::vector<QPoint> possible_points; // Moegliche Punkte bei mouseReleaseEvent
};
}

#endif // SETTINGSHIPSCOORDINATESYSTEM_H
