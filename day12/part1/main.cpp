#include <iostream>
#include <unordered_map>

class Ship
{
    public:
        enum DIRECTION {
            EAST,
            SOUTH,
            WEST,
            NORTH
        };

    public:
        Ship(const int x, const int y, const Ship::DIRECTION direction);
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
        Ship::DIRECTION _direction;
};

Ship::Ship(const int x, const int y, const Ship::DIRECTION direction):
    _x(x), _y(y), _direction(direction)
{
}

void Ship::forward(const int value)
{
    if (_direction == Ship::DIRECTION::EAST) {
        _x += value;
    } else if (_direction == Ship::DIRECTION::SOUTH) {
        _y -= value;
    } else if (_direction == Ship::DIRECTION::WEST) {
        _x -= value;
    } else if (_direction == Ship::DIRECTION::NORTH) {
        _y += value;
    }
}

void Ship::rotateLeft(const int value)
{
    size_t currentDirection = 0;
    Ship::DIRECTION directions[4] = {
        EAST, NORTH, WEST, SOUTH
    };

    size_t directionsSize = sizeof(directions) / sizeof(Ship::DIRECTION);
    for (; currentDirection < directionsSize; currentDirection++)
        if (directions[currentDirection] == _direction)
            break;

    int valueIndex = (currentDirection + (value / 90)) % directionsSize;
    _direction = directions[valueIndex];
}

void Ship::rotateRight(const int value)
{
    size_t currentDirection = 0;
    Ship::DIRECTION directions[4] = {
        EAST, SOUTH, WEST, NORTH
    };

    size_t directionsSize = sizeof(directions) / sizeof(Ship::DIRECTION);
    for (; currentDirection < directionsSize; currentDirection++)
        if (directions[currentDirection] == _direction)
            break;

    int valueIndex = (currentDirection + (value / 90)) % directionsSize;
    _direction = directions[valueIndex];
}

void Ship::eastAction(const int value)
{
    _x += value;
}

void Ship::southAction(const int value)
{
    _y -= value;
}

void Ship::westAction(const int value)
{
    _x -= value;
}

void Ship::northAction(const int value)
{
    _y += value;
}

int Ship::getX(void) const
{
    return _x;
}

int Ship::getY(void) const
{
    return _y;
}

int main(void)
{
    std::string line;

    Ship ship(0, 0, Ship::DIRECTION::EAST);
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
