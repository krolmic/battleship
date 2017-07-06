#include "ship.h"

MODEL::Ship::Ship(int id, MODEL::Point p1, MODEL::Point p2)
    : id{id}, p1{p1}, p2{p2}, criticalHit{false}
{
}

MODEL::Ship::~Ship()
{
}

void MODEL::Ship::setCriticalHit(bool criticalHit)
{
    this->criticalHit = criticalHit;
}

int MODEL::Ship::getId()
{
    return(this->id);
}

MODEL::Point MODEL::Ship::getP1() const
{
    return(this->p1);
}

MODEL::Point MODEL::Ship::getP2() const
{
    return(this->p2);
}

bool MODEL::Ship::isDestroyed()
{
    if(hitList.size() >= 2 || criticalHit == true)
        return(true);
    else
        return(false);
}

bool MODEL::Ship::isDestroyedCritical()
{
    if(criticalHit)
        return(true);
    else
        return(false);
}

void MODEL::Ship::addHit(double x, double y)
{
    hitList.emplace_back(MODEL::Point(x, y));
}
