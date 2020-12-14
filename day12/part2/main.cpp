#include <iostream>
#include <unordered_map>

#include "Ship.hpp"

int main(void)
{
    std::string line;

    Ship ship(0, 0, DIRECTION::EAST, Waypoint(10, 1));
    std::unordered_map<std::string, void (Ship::*)(const int value)> mPtrs;

    mPtrs.emplace("N", &Ship::northAction);
    mPtrs.emplace("S", &Ship::southAction);
    mPtrs.emplace("E", &Ship::eastAction);
    mPtrs.emplace("W", &Ship::westAction);
    mPtrs.emplace("L", &Ship::rotateLeft);
    mPtrs.emplace("R", &Ship::rotateRight);
    mPtrs.emplace("F", &Ship::forward);

    while (std::getline(std::cin, line)) {
        std::string action = line.substr(0, 1);
        std::string value = line.substr(1);

        ((ship).*(mPtrs[action]))(std::stoi(value));
    }

    std::cout << abs(ship.getX()) + abs(ship.getY()) << std::endl;

    return 0;
}
