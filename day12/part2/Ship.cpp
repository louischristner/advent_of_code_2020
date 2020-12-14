#include "Ship.hpp"

Ship::Ship(const int x, const int y, const DIRECTION direction, const Waypoint waypoint):
    _x(x), _y(y), _direction(direction), _waypoint(waypoint)
{
}

void Ship::forward(const int value)
{
    _x += _waypoint.getX() * value;
    _y += _waypoint.getY() * value;
}

void Ship::rotateLeft(const int value)
{
    int s = std::sin(value * (M_PI / 180.0f));
    int c = std::cos(value * (M_PI / 180.0f));

    int newX = _waypoint.getX() * c - _waypoint.getY() * s;
    int newY = _waypoint.getX() * s + _waypoint.getY() * c;

    _waypoint.setX(newX);
    _waypoint.setY(newY);
}

void Ship::rotateRight(const int value)
{
    int s = std::sin(value * (M_PI / 180.0f));
    int c = std::cos(value * (M_PI / 180.0f));

    int newX = _waypoint.getX() * c + _waypoint.getY() * s;
    int newY = _waypoint.getY() * c - _waypoint.getX() * s;

    _waypoint.setX(newX);
    _waypoint.setY(newY);
}

void Ship::eastAction(const int value)
{
    _waypoint.setX(_waypoint.getX() + value);
}

void Ship::southAction(const int value)
{
    _waypoint.setY(_waypoint.getY() - value);
}

void Ship::westAction(const int value)
{
    _waypoint.setX(_waypoint.getX() - value);
}

void Ship::northAction(const int value)
{
    _waypoint.setY(_waypoint.getY() + value);
}

int Ship::getX(void) const
{
    return _x;
}

int Ship::getY(void) const
{
    return _y;
}
