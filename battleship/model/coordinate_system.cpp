#include "coordinate_system.h"
#include <stdexcept>

MODEL::CoordinateSystem::CoordinateSystem()
{

}

bool MODEL::CoordinateSystem::addShip(MODEL::Point p1, MODEL::Point p2)
{
    int shipId = shipList.size(); //ship id would be equal the index of the vector
    if (shipId >= MAX_SHIP_COUNT) {
        throw std::length_error{"you can set only 5 ship, not more."};
    }
    shipList.emplace_back(shipId, p1, p2);
    
    return (shipId + 1) == MAX_SHIP_COUNT; //true if 5th (index: 4) ship have been added
}

