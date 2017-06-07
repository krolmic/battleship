#include "coordinatesystem.h"
#include <qpainter.h>
#include <iostream>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>

CoordinateSystem::CoordinateSystem(QWidget *parent)
: QWidget(parent)
{
    target_pixmap = new QPixmap(this->width,this->length);
    target_pixmap->fill();
    paintAxis();

    initial_x = 0;
    initial_y = 0;
    final_x = 0;
    final_y = 0;

    mouse_pressed = false;
    fillPointsList();
}

CoordinateSystem::~CoordinateSystem()
{
}

QPoint CoordinateSystem::getNextPointFromVector(int x, int y, std::vector<QPoint>& v)
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

void CoordinateSystem::clearInvalidPossiblePoints()
{
    for(std::vector<QPoint>::iterator it = possible_points.begin(); it != possible_points.end();)
    {
        if(it->x() < 0 || it->y() < 0 || it->x() > width || it->y() > width)
        {
            qWarning() << Q_FUNC_INFO << "ein Punkt ausserhalb des Spielfelds wurde gefunden";
            qWarning() << Q_FUNC_INFO << "Punkt: (x:" << it->x() << "y:" << it->y() << ")";
            it = possible_points.erase(it);
        }
        else
            ++it;
    }
}

void CoordinateSystem::fillPointsList()
{
    for(int y=0; y<length; y+= length/space_to_next_line)
        for(int x=0; x<width; x += width/space_to_next_line)
        {
            points.push_back(QPoint(x, y));
        }
}

void CoordinateSystem::paintAxis()
{
    QPainter pixmap_painter(target_pixmap);

    QPen pen2(lines_color);
    QPen pen1(x_y_axis_color);
    pen1.setWidth(2);
    pixmap_painter.setPen(pen2);

    for(int i=0; i<width; i+= width/space_to_next_line)
    {
        pixmap_painter.drawLine(i, 0, i, length);
        if(i == (width/space_to_next_line) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(i, 0, i, length);
            pixmap_painter.setPen(pen2);
        }
    }

    for(int i=0; i<length; i+= length/space_to_next_line)
    {
        pixmap_painter.drawLine(0, i, length, i);
        if(i == (width/space_to_next_line) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(0, i, length, i);
            pixmap_painter.setPen(pen2);
        }
    }
}

void CoordinateSystem::paintShips()
{
    if(!ships.empty())
    {
        QPainter pixmap_painter(target_pixmap);
        QPen pen(ships_color);
        pen.setWidth(2);
        pixmap_painter.setPen(pen);

        for(auto s : ships)
        {
            pixmap_painter.drawLine(s);
        }
    }
}

void CoordinateSystem::mousePressEvent(QMouseEvent* event)
{
      mouse_pressed = true;
      QPoint p = getNextPointFromVector(event->pos().x(), event->pos().y(), points);
      initial_x = p.x();
      initial_y = p.y();
}

void CoordinateSystem::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_pressed = false;
    QLine l(initial_x, initial_y, final_x, final_y);
    ships.push_back(l);
}

void CoordinateSystem::paintEvent(QPaintEvent *e)
{
    if(mouse_pressed)
    {
        QPainter pixmap_painter(target_pixmap);
        QPen pen(ships_color);
        pen.setWidth(2);
        pixmap_painter.setPen(pen);
        pixmap_painter.drawLine(initial_x, initial_y, final_x, final_y);
    }
    QPainter painter(this);
    painter.drawPixmap(0, 0, *target_pixmap);
}

void CoordinateSystem::mouseMoveEvent(QMouseEvent *event)
{
    // TODO: das "richtige" Event abfragen
    if (event->type() == QGraphicsSceneMouseEvent::MouseMove)
    {
        QPainter pixmap_painter(target_pixmap);
        QPen pen(bg_color);
        pen.setWidth(2);
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
            qDebug() << "x:" << p.x() << "y:" << p.y();


        QPoint p = getNextPointFromVector(event->pos().x(), event->pos().y(), possible_points);

        final_x = p.x();
        qDebug() << "initial_x:" << initial_x << "initial_y:" << initial_y;
        final_y = p.y();
    }
    update();
    paintAxis();
    paintShips();
}
