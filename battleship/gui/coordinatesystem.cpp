#include "coordinatesystem.h"
#include <qpainter.h>
#include <iostream>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>

using namespace GUI;

CoordinateSystem::CoordinateSystem(QWidget *parent)
: QWidget(parent)
{
    target_pixmap = new QPixmap(this->gamearea,this->gamearea);
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

void CoordinateSystem::fillPointsList()
{
    for(int y=0; y<=gamearea; y+= gamearea/space_to_next_line)
        for(int x=0; x<=gamearea; x += gamearea/space_to_next_line)
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

    for(int i=space_to_next_line; i<gamearea; i+= gamearea/space_to_next_line)
    {
        pixmap_painter.drawLine(i, 0, i, gamearea);
        if(i == (gamearea/space_to_next_line) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(i, 0, i, gamearea);
            pixmap_painter.setPen(pen2);
        }
    }

    for(int i=space_to_next_line; i<gamearea; i+= gamearea/space_to_next_line)
    {
        pixmap_painter.drawLine(0, i, gamearea, i);
        if(i == (gamearea/space_to_next_line) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(0, i, gamearea, i);
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
        pen.setWidth(3);
        pixmap_painter.setPen(pen);

        for(auto s : ships)
        {
            pixmap_painter.drawLine(s);
        }
    }
}

