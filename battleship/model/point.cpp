#include "point.h"

MODEL::Point::Point(double x, double y)
    : x{x}, y{y}
{
}

double MODEL::Point::getX()
{
    return x;
}

double MODEL::Point::getY()
{
    return y;
}

