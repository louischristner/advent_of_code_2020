#include "Waypoint.hpp"

Waypoint::Waypoint(const int x, const int y):
    _x(x), _y(y)
{
}

void Waypoint::setX(const int x)
{
    _x = x;
}

void Waypoint::setY(const int y)
{
    _y = y;
}

int Waypoint::getX(void) const
{
    return _x;
}

int Waypoint::getY(void) const
{
    return _y;
}
