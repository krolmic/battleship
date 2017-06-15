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

    void nextShipPoint(int&, int&, int, int);
    bool isValidDistance(int, int, int, int);
    bool isValidPlacement(int, int, int, int);

    // Aktualisieren des Koordinatensystems
    void paintAxis();
    void paintShips();
    void clearField();

    // Events
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *event);

    std::vector<QLine> ships;
    QPixmap *target_pixmap;
    // Farben
    Qt::GlobalColor lines_color = Qt::gray;
    Qt::GlobalColor x_y_axis_color = Qt::black;
    Qt::GlobalColor ships_color = Qt::blue;
    Qt::GlobalColor bg_color = Qt::white;


private:
    // TODO: Namen verbessern
    QWidget *parent;
    //QPainter *pixmap_painter;

    std::vector<QPoint> points; // Alle punkte des Koordinatensystems
    std::vector<QPoint> possible_points; // Moegliche Punkte bei mouseReleaseEvent





    // TODO: ein Wert statt width und length, da das Spielfeld immer ein Quadrat bleibt
    int gamearea = 400;
    int width = 400;
    int length = 400;
    int space_to_next_line = 20;
    int ship_length = (length/space_to_next_line)*2;
    int initial_x = 0;
    int initial_y = 0;
    int final_x = 0;
    int final_y = 0;


    bool mouse_pressed = false;

};

#endif // COORDINATESYSTEM_H
