#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H
#include <qwidget.h>
#include <QGraphicsView>
#include <memory>

namespace GUI
{
/// Abstrakte Klasse
class CoordinateSystem : public QWidget
{
public:
    explicit CoordinateSystem(QWidget *parent = nullptr);
    ~CoordinateSystem();

    /// zeichnet die Beschriftungen der X- und Y-Achse
    void paintText();
    /// zeichnet die X- und Y-Achse
    void paintAxis();
    /// zeichnet die Schiffe aus ships
    void paintShips();
    /// Eine Funktion, die pure virtual ist, wird fuer eine abstrakte Klasse benoetigt
    virtual void clearField() = 0;
    /// Rechnet die Pixel-Koordinaten eines QPoint in der GUI in die mathematisch richtige Werte um und gibt sie zurueck
    QPoint getCoordinates(int x, int y);

    /// Schiffe
    std::vector<QLine> ships;
    /// Pain Device fuer das Koordinatensystem
    QPixmap *target_pixmap;
    /// Farben
    Qt::GlobalColor lines_color = Qt::gray;
    Qt::GlobalColor x_y_axis_color = Qt::black;
    Qt::GlobalColor ships_color = Qt::blue;
    Qt::GlobalColor bg_color = Qt::white;

protected:
    // TODO: Namen verbessern
    QWidget *parent;
    /// Alle Schnittpunkte der Linien auf dem Koordinatensystem
    std::vector<QPoint> points;

    int gamearea = 400;
    int space_to_next_line = 20;
    int ship_length = (gamearea/space_to_next_line)*2;
    /// die Ausgangskoordinaten
    int initial_x = -1;
    int initial_y = -1;
    /// die Endkoordinaten
    int final_x = -1;
    int final_y = -1;
    /// wird beim mousePressEvent auf true gesetzt
    bool mouse_pressed = false;
    /// bestimmt die Groesse der Pfeile an den Achsen des Koordinatensystems
    int triangle_size = 5;


};
}

#endif // COORDINATESYSTEM_H
