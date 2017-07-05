#ifndef POINT_H
#define POINT_H

namespace MODEL {

class Point
{
public:
    explicit Point(double x, double y);
    
    double getX();
    double getY();
    
private:
    double x;
    double y;
};

} //end NS
#endif // POINT_H
