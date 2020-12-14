#ifndef SHIP_HPP_
#define SHIP_HPP

#include <cmath>
#include <cstdlib>
#include <iostream>

#include "Waypoint.hpp"

enum class DIRECTION {
    EAST,
    SOUTH,
    WEST,
    NORTH
};

class Ship
{
    public:
        Ship(const int x, const int y, const DIRECTION direction, const Waypoint waypoint);
        ~Ship() = default;

        void forward(const int value);
        void rotateLeft(const int value);
        void rotateRight(const int value);

        void eastAction(const int value);
        void southAction(const int value);
        void westAction(const int value);
        void northAction(const int value);

        int getX(void) const;
        int getY(void) const;

    protected:
    private:
        int _x;
        int _y;
        DIRECTION _direction;
        Waypoint _waypoint;
};

#endif /* !SHIP_HPP_ */
