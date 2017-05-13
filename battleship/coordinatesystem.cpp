#include "coordinatesystem.h"
#include <qpainter.h>

CoordinateSystem::CoordinateSystem()
{
}

CoordinateSystem::~CoordinateSystem()
{

}

void CoordinateSystem::paintEvent(QPaintEvent * event)
{
    QPainter pn(this);

    int w_2 = width() / 2;
    int h_2 = height() / 2;

    { // X- and Y-Axis drawing
        pn.setPen( Qt::blue );
        pn.drawLine( 0, h_2, width(), h_2);     // X-Axis
        pn.drawLine( w_2, 0 , w_2, height() );  // Y-Axis
    }

    QMatrix m;
    m.translate( w_2, h_2 );
    m.scale( 1, -1 );
}

