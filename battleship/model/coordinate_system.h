#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <deque>
#include "ship.h"

namespace MODEL {

class Point;
/// A class that stores data of coordinate system separately from the graphical interface
class CoordinateSystem
{
public:
    explicit CoordinateSystem();
    
    CoordinateSystem(CoordinateSystem const &) = delete; //disable copy-constructor
    CoordinateSystem& operator=(CoordinateSystem const &other) = delete; //disable assign-operator
    CoordinateSystem(CoordinateSystem&& other) = delete; //disable move-constructor
    CoordinateSystem& operator=(CoordinateSystem&& other) = delete; //disable move assign-operator
    
    /**
     * @see ModelInterface#placeShip(MODEL::Point, MODEL::Point)
     * 
     * @return true if 5 ships have been added
     * @throws std::length_error on attempt to add more than 5 ships
     */
    bool addShip(MODEL::Point p1, MODEL::Point p2);
    
private:
    static constexpr int MAX_SHIP_COUNT{5};
    
    std::deque<MODEL::Ship> shipList; //using deque instead of vector allows to store none-movable, none-copyable objects
};

} // end NS
#endif // COORDINATESYSTEM_H
