#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>

namespace GUI
{
// Wird nur als Basis-Klasse benutzt
class CoordinateSystem : public QWidget
{
public:
    explicit CoordinateSystem(QWidget *parent = nullptr);
    ~CoordinateSystem();

    void fillPointsList();

    // Aktualisieren des Koordinatensystems
    void paintAxis();
    void paintShips();
    // Eine Funktion, die pure virtual ist, wird fuer eine abstrakte Klasse benoetigt
    virtual void clearField() = 0;

    std::vector<QLine> ships;
    QPixmap *target_pixmap;
    // Farben
    Qt::GlobalColor lines_color = Qt::gray;
    Qt::GlobalColor x_y_axis_color = Qt::black;
    Qt::GlobalColor ships_color = Qt::blue;
    Qt::GlobalColor bg_color = Qt::white;

protected:
    // TODO: Namen verbessern
    QWidget *parent;
    //QPainter *pixmap_painter;

    std::vector<QPoint> points; // Alle punkte des Koordinatensystems

    int gamearea = 400;

    int space_to_next_line = 20;
    int ship_length = (gamearea/space_to_next_line)*2;
    int initial_x = 0;
    int initial_y = 0;
    int final_x = 0;
    int final_y = 0;

    bool mouse_pressed = false;
};
}

#endif // COORDINATESYSTEM_H
