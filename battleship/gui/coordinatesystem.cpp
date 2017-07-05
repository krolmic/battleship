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
    pixmap_painter.setFont( QFont("Arial", 7,QFont::Light));

    // TODO: Member in der Klasse
    int step{gamearea/space_to_next_line};
    int number{10};
    for(int i=0; i<=gamearea; i+= step)
    {
        pixmap_painter.drawLine(i, 0, i, gamearea);
        if(number < 10 && number > -10)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(i,((step) * space_to_next_line/2),i,((step) * space_to_next_line/2)+3);
            pixmap_painter.drawText((QPoint(((step) * space_to_next_line/2)-13, i-3)), std::to_string(number).c_str());
            pixmap_painter.setPen(pen2);
        }
        if(i == (step) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(i, 0, i, gamearea);
            pixmap_painter.setPen(pen2);
        }
        --number;
    }

    number = -10;
    for(int i=0; i<=gamearea; i+= step)
    {
        pixmap_painter.drawLine(0, i, gamearea, i);
        if(number < 10 && number > -10)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(((step) * space_to_next_line/2),i,((step) * space_to_next_line/2)-3,i);
            pixmap_painter.drawText(QPoint(i,((step) * space_to_next_line/2)+13), std::to_string(number).c_str());
            pixmap_painter.setPen(pen2);
        }
        if(i == (step) * space_to_next_line/2)
        {
            pixmap_painter.setPen(pen1);
            pixmap_painter.drawLine(0, i, gamearea, i);
            pixmap_painter.setPen(pen2);
        }
        ++number;
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

// TODO: umbenennen
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

QPoint CoordinateSystem::getCoordinates(int x, int y)
{
    qDebug() << Q_FUNC_INFO << "args:" << x << y;
    float result_x = (((float)x/gamearea)*space_to_next_line)-10;
    float result_y = (((float)y/gamearea)*space_to_next_line)-10;
    qDebug() << Q_FUNC_INFO << "result:" << result_x << result_y;
    return QPoint(result_x,result_y);
}
