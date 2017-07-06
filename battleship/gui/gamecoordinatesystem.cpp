#include "gamecoordinatesystem.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QLine>
#include "model/ship.h"

using namespace GUI;

GUI::GameCoordinateSystem::GameCoordinateSystem(QWidget* parent)
    : CoordinateSystem{parent}
{
}


GameCoordinateSystem::~GameCoordinateSystem()
{}

void GameCoordinateSystem::clearField()
{
    qDebug() << Q_FUNC_INFO;
}

void GameCoordinateSystem::mousePressEvent(QMouseEvent* event)
{
    qDebug() << Q_FUNC_INFO;
    mouse_pressed = true;
    initial_x = event->pos().x();
    initial_y = event->pos().y();
}

void GameCoordinateSystem::addShipList(const std::deque<MODEL::Ship>& shipList)
{
    for (auto& ship : shipList) {
        qDebug() << Q_FUNC_INFO << ship.getP1().getX();
    }
}

void GameCoordinateSystem::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    mouse_pressed = false;
    double y = final_y - initial_y;
    double x = final_x - initial_x;
    qDebug() << "x:" << x << "y:" << y;
    int multiplicator{100};
    // TODO: den Multiplicator berechnen
    QLine line(initial_x-x*multiplicator, initial_y-y*multiplicator, final_x+x*multiplicator, final_y+y*multiplicator);
    QPainter pixmap_painter(target_pixmap);
    QPen pen(ships_color);
    pen.setWidth(3);
    pixmap_painter.setPen(pen);
    pixmap_painter.drawLine(line);
    update();

    // TODO: Methoden für Angriffe/Geraden schreiben, shots statt ships
    ships.push_back(line);
}

void GameCoordinateSystem::mouseMoveEvent(QMouseEvent *event)
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
        final_x = event->pos().x();
        final_y = event->pos().y();
    }
    update();
    target_pixmap->fill();
    paintAxis();
    paintShips();
    paintText();
    update();
}

void GameCoordinateSystem::paintEvent(QPaintEvent *event)
{
    if(mouse_pressed)
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
