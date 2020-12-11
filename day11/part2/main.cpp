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
 * 076
 * 1X5
 * 234
 */
std::vector<SEATSTATE> getNeighbours(int x, int y, const std::vector<std::string> &map)
{
    std::vector<SEATSTATE> neighbours;

    for (int i = 1; x - i >= 0 && y - i >= 0; i++) {
        if (map[y - i][x - i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y - i][x - i]));
            break;
        }
    }

    if (neighbours.size() != 1)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; x - i >= 0; i++) {
        if (map[y][x - i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y][x - i]));
            break;
        }
    }

    if (neighbours.size() != 2)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; x - i >= 0 && y + i <= map.size() - 1; i++) {
        if (map[y + i][x - i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y + i][x - i]));
            break;
        }
    }

    if (neighbours.size() != 3)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; y + i <= map.size() - 1; i++) {
        if (map[y + i][x] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y + i][x]));
            break;
        }
    }

    if (neighbours.size() != 4)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; x + i <= map[0].size() - 1 && y + i <= map.size() - 1; i++) {
        if (map[y + i][x + i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y + i][x + i]));
            break;
        }
    }

    if (neighbours.size() != 5)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; x + i <= map[0].size() - 1; i++) {
        if (map[y][x + i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y][x + i]));
            break;
        }
    }

    if (neighbours.size() != 6)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; x + i <= map[0].size() - 1 && y - i >= 0; i++) {
        if (map[y - i][x + i] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y - i][x + i]));
            break;
        }
    }

    if (neighbours.size() != 7)
        neighbours.push_back(SEATSTATE::NONE);

    for (int i = 1; y - i >= 0; i++) {
        if (map[y - i][x] != '.') {
            neighbours.push_back(
                convertToSeatState(map[y - i][x]));
            break;
        }
    }

    if (neighbours.size() != 8)
        neighbours.push_back(SEATSTATE::NONE);

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

                    // std::cout << "---" << std::endl;
                    // std::cout << x << " " << y << std::endl;
                    // std::cout << convertToChar(neighbours[0]) << convertToChar(neighbours[7]) << convertToChar(neighbours[6]) << std::endl;
                    // std::cout << convertToChar(neighbours[1]) << "X" << convertToChar(neighbours[5]) << std::endl;
                    // std::cout << convertToChar(neighbours[2]) << convertToChar(neighbours[3]) << convertToChar(neighbours[4]) << std::endl;

                    if (seats[y][x] == 'L' && std::find(neighbours.begin(), neighbours.end(), SEATSTATE::OCCUPIED) == neighbours.end()) {
                        tmpSeats[y][x] = '#';
                        changed = true;
                    } else if (seats[y][x] == '#' && std::count(neighbours.begin(), neighbours.end(), SEATSTATE::OCCUPIED) >= 5) {
                        tmpSeats[y][x] = 'L';
                        changed = true;
                    }
                }
            }
        }

        seats = tmpSeats;

        // std::cout << "---" << std::endl;
        // for (const std::string &seatRow : seats) {
        //     for (const char &seat : seatRow)
        //         std::cout << seat;
        //     std::cout << std::endl;
        // }

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
