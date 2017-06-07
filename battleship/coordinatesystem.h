#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>


class CoordinateSystem : public QWidget
{
public:
    CoordinateSystem(QWidget *parent = nullptr);
    ~CoordinateSystem();

    void fillPointsList();
    QPoint getNextPointFromVector(int, int, std::vector<QPoint>&);
    void clearInvalidPossiblePoints();

    // Aktualisieren des Koordinatensystems
    void paintAxis();
    void paintShips();

    // Events
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);

private:
    // TODO: Namen verbessern
    QWidget *parent;
    //QPainter *pixmap_painter;
    std::vector<QLine> ships;
    std::vector<QPoint> points; // Alle punkte des Koordinatensystems
    std::vector<QPoint> possible_points; // Moegliche Punkte bei mouseReleaseEvent

    // Farben
    Qt::GlobalColor lines_color = Qt::gray;
    Qt::GlobalColor x_y_axis_color = Qt::black;
    Qt::GlobalColor ships_color = Qt::blue;
    Qt::GlobalColor bg_color = Qt::white;


    // TODO: ein Wert statt width und length, da das Spielfeld immer ein Quadrat bleibt
    int width = 450;
    int length = 450;
    int space_to_next_line = 10;
    int ship_length = (length/space_to_next_line)*2;
    int initial_x = 0;
    int initial_y = 0;
    int final_x = 0;
    int final_y = 0;

    QPixmap *target_pixmap;
    bool mouse_pressed = false;
};

#endif // COORDINATESYSTEM_H
