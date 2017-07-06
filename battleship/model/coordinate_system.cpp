#include "coordinate_system.h"
#include <stdexcept>
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

MODEL::CoordinateSystem::CoordinateSystem()
{

}

MODEL::CoordinateSystem::~CoordinateSystem()
{

}

bool MODEL::CoordinateSystem::addShip(MODEL::Point p1, MODEL::Point p2)
{
    int shipId = shipList.size(); // ship id would be equal the index of the std::deque
    if (shipId >= MAX_SHIP_COUNT) // neccessary? because the Gui allows only to set a fix number of ships
    {
        throw std::length_error{"you can set only 5 ship, not more."};
    }
    shipList.emplace_back(shipId, p1, p2);

    return (shipId + 1) == MAX_SHIP_COUNT; //true if 5th (index: 4) ship have been added
}

bool MODEL::CoordinateSystem::isAllShipPlaced() const
{
    return (shipList.size() == MAX_SHIP_COUNT);
}


void MODEL::CoordinateSystem::calculateShot(double gradient, double y_axis_constant)
{
    std::deque<Ship>::iterator it;

    for(it = shipList.begin(); it != shipList.end(); ++it)
    {
        qDebug() << "Schiff - " <<it->getId() << ":";

        bool gradient_infinity = false;
        bool gradient_null = false;

        // Schiff Koordinaten
        double a_x = it->getP1().getX(); // x1
        double a_y = it->getP1().getY(); // y1
        double b_x = it->getP2().getX(); // x2
        double b_y = it->getP2().getY(); // y2

        qDebug() << "Koordinatenpunkte:";
        qDebug() << "A(" << a_x << "/" << a_y << "), B(" << b_x << "/" << b_y << ")";

        // Erstellung der Geraden aus den Anfangs- und Endpunkten des Schiffes:
        //  - Berechnung der Steigung der Geraden des Schiffes
        double ship_gradient; // Findet nur im Normalfall verwendung
        if(b_x == a_x)
            gradient_infinity = true; //spezialfall bei m = unstd::endlich
        else if(a_y == b_y)
            gradient_null = true; // spezialfall bei m = 0
        else
        {
            ship_gradient = (b_y - a_y) / (b_x - a_x); // Berechnung der Steigung m = (y2 - y1) / (x2 - x1)
            qDebug() << "Steigung = " << ship_gradient << ", ";
        }

        // Die Steigung der Geradengleichung des Schiffes = Unstd::endlich
        //  -> X-Koordinate des Schiffes in die Geradengleichung einsetzen und den Y-Wert ermitteln und mit dem Wertebereich des Schiffes pruefen
        if(gradient_infinity == true)
        {
            qDebug() << "SPEZIALFALL - UNENDlICH:";
            double infinit_sp_y = gradient * a_x + y_axis_constant;
            if(a_y > b_y)
            {
                if(infinit_sp_y <= a_y && infinit_sp_y >= b_y)
                {
                    qDebug() << "[TREFFER - SP(" << a_x << "/" << infinit_sp_y << ")]";
                    it->addHit(a_x, infinit_sp_y);
                }
                else
                    qDebug() << "[KEIN TREFFER]";
            }
            else if(a_y < b_y)
            {
                if(infinit_sp_y >= a_y && infinit_sp_y <= b_y)
                {
                    qDebug() << "[TREFFER - SP(" << a_x << "/" << infinit_sp_y << ")]";
                    it->addHit(a_x, infinit_sp_y);
                }
                else
                    qDebug() << "[KEIN TREFFER]";
            }
            qDebug() << "\n-----------------------------------";
            continue;
        }

        //  Die Steigung der Geradengleichung des Schiffes = 0
        //  -> Y-Koordinate des Schiffes in die Geradengleichung einsetzen und den X-Wert ermitteln und mit dem Wertebereich des Schiffes pruefen
        if(gradient_null == true)
        {
            qDebug() << "SPEZIALFALL - NULL:";
            double null_sp_x = (a_y - y_axis_constant) / gradient;
            if(a_x > b_x)
            {
                if(null_sp_x <= a_x && null_sp_x >= b_x)
                {
                    qDebug() << "[TREFFER - SP(" << null_sp_x << "/" << a_y << ")]";
                    it->addHit(null_sp_x, a_y);
                }
                else
                    qDebug() << "[KEIN TREFFER]";
            }
            else if(a_x < b_x)
            {
                if(null_sp_x >= a_x && null_sp_x <= b_x)
                {
                    qDebug() << "[TREFFER - SP(" << null_sp_x << "/" << a_y << ")]";
                    it->addHit(null_sp_x, a_y);
                }
                else
                    qDebug() << "[KEIN TREFFER]";
            }
            qDebug() << "\n-----------------------------------";
            continue;
        }

        // -  Berechnung des konstanten Y-Achsenabschnittes der Geraden des Schiffes
        double ship_y_axis_constant = a_y - ship_gradient * a_x;

        qDebug() << "Y-Achsenabschnitt = " << ship_y_axis_constant;

        qDebug() << "Angriffsgleichung: Steigung = " << gradient << ", Y-Achsenabschnitt = " << y_axis_constant;

        // Vergleich der Steigung der Geradengleichungen
        if(ship_gradient == gradient)
        {
            qDebug() << "SELBE STEIGUNG:";
            if(ship_y_axis_constant == y_axis_constant)
            {
                qDebug() << "SELBER Y-ACHSENABSCHNITT:";
                qDebug() << "[IDENTISCH(VOLLTREFFER)]";
                it->setCriticalHit(true);
            }
            else
            {
                qDebug() << "UNTERSCHIEDLICHER Y-ACHSENABSCHNITT:";
                qDebug() << "[PARALLEL(KEIN TREFFER)]";
            }
        }
        else
        {
            qDebug() << "UNTERSCHIEDLICHE STEIGUNG:";

            // Berechnung des Schnittpunktes der beiden Geraden
            double sp_x = (ship_y_axis_constant - y_axis_constant) / (gradient - ship_gradient);
            double sp_y = ship_gradient * sp_x + ship_y_axis_constant;
            qDebug() << "SCHNITTPUNKT(" << sp_x << "/" << sp_y << ")";

            // Pruefen ob der Schnittpunkt im Wertebereich des Schiffes liegt
            bool sp_is_hit = false;
            if(a_x > b_x)
            {
                if(a_y > b_y)
                {
                    if(sp_x <= a_x && sp_x >= b_x && sp_y <= a_y && sp_y >= b_y)
                        sp_is_hit = true;
                }
                else if(a_y < b_y)
                {
                    if(sp_x <= a_x && sp_x >= b_x && sp_y >= a_y && sp_y <= b_y)
                        sp_is_hit = true;
                }
            }
            else if(a_x < b_x)
            {
                if(a_y > b_y)
                {
                    if(sp_x >= a_x && sp_x <= b_x && sp_y <= a_y && sp_y >= b_y)
                        sp_is_hit = true;
                }
                else if(a_y < b_y)
                {
                    if(sp_x >= a_x && sp_x <= b_x && sp_y >= a_y && sp_y <= b_y)
                        sp_is_hit = true;
                }
            }

            // pruefung ob Schnittpunkt ein Treffer war
            if(sp_is_hit == true)
            {
                qDebug() << "[TREFFER - SP(" << sp_x << "/" << sp_y << ")]";
                it->addHit(sp_x, sp_y);
            }
            else
                qDebug() << "[KEIN TREFFER]";
        }
        qDebug() << "\n-----------------------------------";
    }

    // Gibt eine Map mit einer Schiffs-ID als Key und die Treffer als x/y Koordinaten im Vektor als Value der Map zurueck
    // (Falls das Schiff kritisch getroffen wurde, werden Anfangs- und Enpunkte wieder zurueckgegeben)
}

const std::deque<MODEL::Ship>& MODEL::CoordinateSystem::getShipList() const
{
    return shipList;
}


QJsonArray MODEL::CoordinateSystem::getShipListAsJson() const
{
    QJsonArray result;
    for (auto& ship : shipList) {
        result.append(QJsonObject {
            {"x1", ship.getP1().getX()},
            {"y1", ship.getP1().getY()},
            {"x2", ship.getP2().getX()},
            {"y2", ship.getP2().getY()},
        });
    }
    return result;
}







