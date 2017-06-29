#include "settingshipscoordinatesystem.h"
#include <qpainter.h>
#include <iostream>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>

using namespace GUI;

SettingShipsCoordinateSystem::~SettingShipsCoordinateSystem()
{
}

void SettingShipsCoordinateSystem::fillPointsList()
{
    for(int y=0; y<=gamearea; y+= gamearea/space_to_next_line)
        for(int x=0; x<=gamearea; x += gamearea/space_to_next_line)
        {
            points.push_back(QPoint(x, y));
        }
}

QPoint SettingShipsCoordinateSystem::getNextPointFromVector(int x, int y, std::vector<QPoint>& v)
{
    qDebug() << "Starte" << Q_FUNC_INFO << "args:" << x << "," << y;
    int end_x{v.front().x()}, end_y{v.front().y()};
    int new_x_diff{}, best_x_diff{}, new_y_diff{}, best_y_diff{};
    for (auto grid_point : v)
    {
        new_x_diff = std::abs(x - grid_point.x());
        best_x_diff = std::abs(x - end_x);
        new_y_diff = std::abs(y - grid_point.y());
        best_y_diff = std::abs(y - end_y);
        if(new_x_diff < best_x_diff)
            end_x = grid_point.x();
        if (new_y_diff < best_y_diff)
            end_y = grid_point.y();
    }
    qDebug() << "Beendet" << Q_FUNC_INFO << "end_x:" << end_x << " end_y:" << end_y;
    return QPoint(end_x, end_y);
}

void SettingShipsCoordinateSystem::clearInvalidPossiblePoints()
{
    for(std::vector<QPoint>::iterator it = possible_points.begin(); it != possible_points.end();)
    {
        if(it->x() < 0 || it->y() < 0 || it->x() > gamearea || it->y() > gamearea)
        {
            qWarning() << Q_FUNC_INFO << "ein Punkt ausserhalb des Spielfelds wurde gefunden";
            qWarning() << Q_FUNC_INFO << "Punkt: (x:" << it->x() << "y:" << it->y() << ")";
            it = possible_points.erase(it);
        }
        else
            ++it;
    }
}

bool SettingShipsCoordinateSystem::isValidDistance(int x, int y, int x2, int y2)
{
    int valid_diatance_to_next_ship = space_to_next_line/2;
    if(x == x2 && y == y2)
        return false;
    if(x + valid_diatance_to_next_ship == x2 && y == y2)
        return false;
    if(x - valid_diatance_to_next_ship == x2 && y == y2)
        return false;
    if(x == x2 && y + valid_diatance_to_next_ship == y2)
        return false;
    if(x == x2 && y - valid_diatance_to_next_ship == y2)
        return false;
    if(x + valid_diatance_to_next_ship == x2 && y + valid_diatance_to_next_ship == y2)
        return false;
    if(x + valid_diatance_to_next_ship == x2 && y - valid_diatance_to_next_ship == y2)
        return false;
    if(x - valid_diatance_to_next_ship == x2 && y + valid_diatance_to_next_ship == y2)
        return false;
    if(x - valid_diatance_to_next_ship == x2 && y - valid_diatance_to_next_ship == y2)
        return false;

    return true;
}

// Diese Funktion aktualisiert die ersten beiden uebergebenen Werte (x/y) und berechnet diese um eine halbe
// Kaestchenlaenge zu den anderen uebergebenen x/y Werten. Diese Funktion aendert somit die ersten beiden Variablen
// und erhoeht/verringert diese Werte, sodass sie den naechstbesten Punkt des Schiffes wiederspiegeln(halbe Kaestchenlaenge)
void SettingShipsCoordinateSystem::nextShipPoint(int &x, int &y, int x2, int y2)
{
    if(x2 > x)
        x += space_to_next_line/2;

    if(x2 < x)
        x -= space_to_next_line/2;

    if(y2 > y)
        y += space_to_next_line/2;

    if(y2 < y)
        y -= space_to_next_line/2;
}

// Diese Funktion ueberprueft anhand von 2 Koordinatenpunkten(jeweils x/y) ob diese Schiff(Linien)position valide
// ist. Es werden Punkt fuer punkt alle Schiffe mit dem neuen verglichen auf Abstand/Schneidung!
bool SettingShipsCoordinateSystem::isValidPlacement(int x, int y, int dest_x, int dest_y)
{
    if (x == -1 || dest_x == -1 )
        return false;
    // Wurden bereits andere Schiffe gesetzt?
    if(!ships.empty())
    {
        qDebug() << "Ships are already placed. Continue with validation...";
        // Schleife die jedes bereits platzierte Schiff durchläuft
        for(auto s : ships)
        {
            // Startpunkt des neuen Schiffes
            int x_tmp_new = x;
            int y_tmp_new = y;

            // Startpunkt eines bereits gesetzten Schiffes
            int x_tmp = s.x1();
            int y_tmp = s.y1();

            bool new_ship_last_check = false;
            bool ship_last_check = false;

            // Die Schiffe werden mit einem Abstand von einem halben Kaestchen ueberprueft, dabei werden die Punkte entlang des Schiffes(ebenso halbes Kaestchen) verwendet.
            while(true)
            {
                while(true)
                {
                    if(!isValidDistance(x_tmp, y_tmp, x_tmp_new, y_tmp_new))
                        return false;

                    if(ship_last_check == true)
                    {
                        ship_last_check = false;
                        break;
                    }

                    nextShipPoint(x_tmp, y_tmp, s.x2(), s.y2());

                    if(x_tmp == s.x2() && y_tmp == s.y2())
                        ship_last_check = true;
                }

                if(new_ship_last_check == true)
                    break;

                x_tmp = s.x1();
                y_tmp = s.y1();

                nextShipPoint(x_tmp_new, y_tmp_new, dest_x, dest_y);

                if(x_tmp_new == dest_x && y_tmp_new == dest_y)
                    new_ship_last_check = true;
            }
        }
    }
    return true;
}

void SettingShipsCoordinateSystem::mousePressEvent(QMouseEvent* event)
{
    if(points.empty())
        fillPointsList();
    qDebug() << Q_FUNC_INFO;
    mouse_pressed = true;
    QPoint p = getNextPointFromVector(event->pos().x(), event->pos().y(), points);
    initial_x = p.x();
    initial_y = p.y();
    qDebug() << Q_FUNC_INFO << "initial_x:" << initial_x << "initial_y:" << initial_y;
}

void SettingShipsCoordinateSystem::mouseReleaseEvent(QMouseEvent *event)
{

    mouse_pressed = false;
    // TODO: vielleicht ueberfluessig
    if(isValidPlacement(initial_x, initial_y, final_x, final_y))
    {
        QLine l(initial_x, initial_y, final_x, final_y);
        ships.push_back(l);
    }
    initial_x = -1;
    initial_y = -1;
    final_x = -1;
    final_y = -1;

}

void SettingShipsCoordinateSystem::paintEvent(QPaintEvent *e)
{

    if(mouse_pressed && isValidPlacement(initial_x, initial_y, final_x, final_y) && initial_x != -1)
    {
        QPainter pixmap_painter(target_pixmap);
        QPen pen(ships_color);
        pen.setWidth(3);
        pixmap_painter.setPen(pen);
        pixmap_painter.drawLine(initial_x, initial_y, final_x, final_y);
    }
    QPainter painter(this);
    painter.drawPixmap(0, 0, *target_pixmap);
}

void SettingShipsCoordinateSystem::mouseMoveEvent(QMouseEvent *event)
{
    // TODO: das "richtige" Event abfragen
    if (event->type() == QGraphicsSceneMouseEvent::MouseMove)
    {
        QPainter pixmap_painter(target_pixmap);
        QPen pen(bg_color);
        pen.setWidth(3);
        pixmap_painter.setPen(pen);
        pixmap_painter.drawLine(initial_x, initial_y, final_x, final_y);
        update();
        possible_points.clear();
        // Definition der moeglichen Punkte
        // TODO: eine Funktion daraus machen
        possible_points.push_back(QPoint(initial_x, initial_y - ship_length));                  // x, y - l
        possible_points.push_back(QPoint(initial_x + ship_length, initial_y - ship_length));    // x + l, y - l
        possible_points.push_back(QPoint(initial_x + ship_length, initial_y));                  // x + l, y
        possible_points.push_back(QPoint(initial_x + ship_length, initial_y + ship_length));    // x + l, y + l
        possible_points.push_back(QPoint(initial_x, initial_y + ship_length));                  // x, y + l
        possible_points.push_back(QPoint(initial_x - ship_length, initial_y + ship_length));    // x - l, y + l
        possible_points.push_back(QPoint(initial_x - ship_length, initial_y));                  // x - l, y
        possible_points.push_back(QPoint(initial_x - ship_length, initial_y - ship_length));    // x - l, y - l
        clearInvalidPossiblePoints();
        qDebug() << "possible_points:";
        for(QPoint p : possible_points)
        {
            qDebug() << "x:" << p.x() << "y:" << p.y();

            qDebug() << "is VALID!";
        }
        QPoint p = getNextPointFromVector(event->pos().x(), event->pos().y(), possible_points);

        if (initial_x != -1)
        {
            final_x = p.x();
            qDebug() << "initial_x:" << initial_x << "initial_y:" << initial_y;
            final_y = p.y();
        }
    }
    update();
    paintAxis();
    paintShips();
    paintText();
}

void SettingShipsCoordinateSystem::clearField()
{
    if(!ships.empty())
    {
        qDebug() << Q_FUNC_INFO << "ships ist nicht leer";
        QPainter pixmap_painter(target_pixmap);
        QPen pen(bg_color);
        pen.setWidth(3);
        pixmap_painter.setPen(pen);

        for(auto s : ships)
        {
            pixmap_painter.drawLine(s);
        }
    }
    update();
    paintAxis();
    ships.clear();
}

