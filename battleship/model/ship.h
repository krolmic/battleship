#ifndef SHIP_H
#define SHIP_H

#include "point.h"
#include <deque>

namespace MODEL {

/// A simple class representing a ship with its coordinates of hits made by a linear equation
class Ship
{
public:
    explicit Ship(int ship_id, Point p1, Point p2);
    ~Ship();

    Ship(Ship const &) = delete; //disable copy-constructor
    Ship& operator=(Ship const &other) = delete; //disable assign-operator
    Ship(Ship&& other) = delete; //disable move-constructor
    Ship& operator=(Ship&& other) = delete; //disable move assign-operator

    void setCriticalHit(bool criticalHit);

    int getId();
    Point getP1() const;
    Point getP2() const;

    /// Checks if the ship is already destroyed
    bool isDestroyed();

    /// Checks if the ship was destroyed by a critical hit
    bool isDestroyedCritical();

    /// Add a hit to the list of hitted coordinates
    void addHit(double x, double y);

private:
    int id;
    Point p1;
    Point p2;
    bool criticalHit;
    std::deque<Point> hitList;
};

} // end NS
#endif // SHIP_H
