#include <vector>
#include <iostream>
#include <algorithm>

enum class SEATSTATE {
    EMPTY,
    OCCUPIED,
    FLOOR,
    NONE
};

SEATSTATE convertToSeatState(const char &c)
{
    if (c == 'L') {
        return SEATSTATE::EMPTY;
    } else if (c == '#') {
        return SEATSTATE::OCCUPIED;
    } else if (c == '.') {
        return SEATSTATE::FLOOR;
    } else {
        return SEATSTATE::NONE;
    }
}

char convertToChar(const SEATSTATE &s)
{
    if (s == SEATSTATE::EMPTY) {
        return 'L';
    } else if (s == SEATSTATE::OCCUPIED) {
        return '#';
    } else if (s == SEATSTATE::FLOOR) {
        return '.';
    } else {
        return '?';
    }
}

/**
 * 187
 * 2X6
 * 345
 */
std::vector<SEATSTATE> getNeighbours(int x, int y, const std::vector<std::string> &map)
{
    std::vector<SEATSTATE> neighbours;

    if (x > 0) {
        if (y > 0) {
            neighbours.push_back(
                convertToSeatState(map[y - 1][x - 1]));
        } else {
            neighbours.push_back(SEATSTATE::NONE);
        }

        neighbours.push_back(
            convertToSeatState(map[y][x - 1]));

        if (y < map.size() - 1) {
            neighbours.push_back(
                convertToSeatState(map[y + 1][x - 1]));
        } else {
            neighbours.push_back(SEATSTATE::NONE);
        }

    } else {
        neighbours.push_back(SEATSTATE::NONE);
        neighbours.push_back(SEATSTATE::NONE);
        neighbours.push_back(SEATSTATE::NONE);
    }

    if (y < map.size() - 1) {
        neighbours.push_back(
            convertToSeatState(map[y + 1][x]));
    } else {
        neighbours.push_back(SEATSTATE::NONE);
    }

    if (x < map[0].size() - 1) {
        if (y < map.size() - 1) {
            neighbours.push_back(
                convertToSeatState(map[y + 1][x + 1]));
        } else {
            neighbours.push_back(SEATSTATE::NONE);
        }

        neighbours.push_back(
            convertToSeatState(map[y][x + 1]));

        if (y > 0) {
            neighbours.push_back(
                convertToSeatState(map[y - 1][x + 1]));
        } else {
            neighbours.push_back(SEATSTATE::NONE);
        }

    } else {
        neighbours.push_back(SEATSTATE::NONE);
        neighbours.push_back(SEATSTATE::NONE);
        neighbours.push_back(SEATSTATE::NONE);
    }

    if (y > 0) {
        neighbours.push_back(
            convertToSeatState(map[y - 1][x]));
    } else {
        neighbours.push_back(SEATSTATE::NONE);
    }

    return neighbours;
}

int main(void)
{
    std::string line;
    std::vector<std::string> seats;

    while (std::getline(std::cin, line))
        seats.push_back(line);

    size_t sizeY = seats.size();
    size_t sizeX = seats[0].size();


    while (true) {
        bool changed = false;
        std::vector<std::string> tmpSeats = seats;

        for (size_t y = 0; y < sizeY; y++) {
            for (size_t x = 0; x < sizeX; x++) {
                if (seats[y][x] != '.') {
                    std::vector<SEATSTATE> neighbours =
                        getNeighbours(x, y, seats);

                    if (seats[y][x] == 'L' && std::find(neighbours.begin(), neighbours.end(), SEATSTATE::OCCUPIED) == neighbours.end()) {
                        tmpSeats[y][x] = '#';
                        changed = true;
                    } else if (seats[y][x] == '#' && std::count(neighbours.begin(), neighbours.end(), SEATSTATE::OCCUPIED) >= 4) {
                        tmpSeats[y][x] = 'L';
                        changed = true;
                    }
                }
            }
        }

        seats = tmpSeats;

        if (changed == false) {
            break;
        }
    }

    size_t occupied = 0;
    for (const std::string &seatRow : seats)
        for (const char &seat : seatRow)
            if (seat == '#')
                occupied += 1;

    std::cout << occupied << std::endl;

    return 0;
}
