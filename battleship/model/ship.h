#ifndef SHIP_H
#define SHIP_H

#include "point.h"

namespace MODEL {

/// A class representing a ship
class Ship
{
public:
    explicit Ship(int id, Point p1, Point p2);
    
    Ship(Ship const &) = delete; //disable copy-constructor
    Ship& operator=(Ship const &other) = delete; //disable assign-operator
    Ship(Ship&& other) = delete; //disable move-constructor
    Ship& operator=(Ship&& other) = delete; //disable move assign-operator
    
private:
    int id;
    Point p1;
    Point p2;
};

} // end NS
#endif // SHIP_H
