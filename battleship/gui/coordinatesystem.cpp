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
    // TODO: fit the pixmap to the layout

    target_pixmap = new QPixmap(this->gamearea*1.005,this->gamearea*1.005);
    target_pixmap->fill();
    paintAxis();
    paintText();
    mouse_pressed = false;
}

CoordinateSystem::~CoordinateSystem()
{
}



void CoordinateSystem::paintAxis()
{
    QPainter pixmap_painter(target_pixmap);

    QPen pen2(lines_color);
    QPen pen1(x_y_axis_color);
    pen1.setWidth(2);
    pixmap_painter.setPen(pen2);

    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    // TODO: Member in der Klasse
    int step{gamearea/space_to_next_line};
    for(int i=0; i<=gamearea; i+= step)
    {
        pixmap_painter.drawLine(i, 0, i, gamearea);
        if(i == (step) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(i, 0, i, gamearea);
            pixmap_painter.setPen(pen2);
        }
    }

    for(int i=0; i<=gamearea; i+= step)
    {
        pixmap_painter.drawLine(0, i, gamearea, i);
        if(i == (step) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(0, i, gamearea, i);
            pixmap_painter.setPen(pen2);
        }
    }

    // x-arrow
    QPolygon poly;
    poly << QPoint(gamearea,(step) * space_to_next_line/2)
         << QPoint(gamearea-triangle_size,((step) * space_to_next_line/2)-triangle_size)
         << QPoint(gamearea-triangle_size,((step) * space_to_next_line/2)+triangle_size);

    QPainterPath path;
    path.addPolygon(poly);

    // y-arrow
    poly.clear();
    poly << QPoint((step) * space_to_next_line/2, 0)
         << QPoint((step) * space_to_next_line/2-triangle_size,triangle_size)
         << QPoint((step) * space_to_next_line/2+triangle_size,triangle_size);

    path.addPolygon(poly);
    // paint the arrows
    pixmap_painter.fillPath(path, brush);
    //paintText();
}

void CoordinateSystem::paintText()
{
    int step{gamearea/space_to_next_line};
    QPainter pixmap_painter(target_pixmap);
    QPen pen1(x_y_axis_color);
    pixmap_painter.setPen(pen1);
    pixmap_painter.setFont( QFont("Arial", 10,QFont::Bold) );
    pixmap_painter.drawText((QPoint(((step) * space_to_next_line/2)+8, 15)), "y");
    pixmap_painter.drawText(QPoint(gamearea-15,(step) * space_to_next_line/2 - 8), "x");
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

