#include <vector>
#include <iostream>
#include <algorithm>

struct Vect2D
{
    int x;
    int y;
};

struct Vect3D
{
    int x;
    int y;
    int z;
};

enum State
{
    ACTIVE,
    INACTIVE
};

void display(const std::vector<std::vector<std::string>> &pocket, Vect2D size, size_t currentCycle, size_t maxCycle)
{
    std::cout << ((currentCycle == 0) ? "Before any cycle" : "After " + std::to_string(currentCycle) + " cycle") << std::endl;

    for (int z = 0; z < pocket.size(); z++) {

        bool hasActiveCell = false;
        for (int y = 0; y < pocket[z].size(); y++)
            for (int x = 0; x < pocket[z][y].size(); x++)
                if (pocket[z][y][x] == '#')
                    hasActiveCell = true;

        if (!hasActiveCell)
            continue;

        std::cout << std::endl << "z=" << z << std::endl;
        for (int y = 0; y < pocket[z].size(); y++) {
            for (int x = 0; x < pocket[z][y].size(); x++)
                std::cout << pocket[z][y][x];
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

size_t countActiveNeighbors(const std::vector<std::vector<std::string>> &pocket, const std::vector<Vect3D> &neighbors)
{
    size_t result = 0;
    size_t zSize = pocket.size();
    size_t ySize = pocket[0].size();
    size_t xSize = pocket[0][0].size();

    for (const Vect3D &neighbor : neighbors)
        if (neighbor.x >= 0 && neighbor.y >= 0 && neighbor.z >= 0 && neighbor.x <= xSize - 1 && neighbor.y <= ySize - 1 && neighbor.z <= zSize - 1)
            if (pocket[neighbor.z][neighbor.y][neighbor.x] == '#')
                result += 1;

    return result;
}

std::vector<Vect3D> getNeighbors(const std::vector<std::vector<std::string>> &pocket, const Vect3D pos)
{
    std::vector<Vect3D> neighbors;

    for (int z = pos.z - 1; z <= pos.z + 1; z++)
        for (int y = pos.y - 1; y <= pos.y + 1; y++)
            for (int x = pos.x - 1; x <= pos.x + 1; x++)
                if (x != pos.x || y != pos.y || z != pos.z)
                    neighbors.push_back({x, y, z});

    return neighbors;
}

void compute(std::vector<std::vector<std::string>> &pocket, Vect2D size, size_t currentCycle, size_t maxCycle)
{
    display(pocket, size, currentCycle, maxCycle);
    if (currentCycle == maxCycle)
        return;

    size_t ySize = pocket[0].size();
    size_t xSize = pocket[0][0].size();
    std::vector<std::vector<std::string>> newPocket = pocket;

    for (int z = 0; z < (maxCycle * 2) + 1; z++) {
        for (int y = 0; y < ySize; y++) {
            for (int x = 0; x < xSize; x++) {
                std::vector<Vect3D> neighbourgs = getNeighbors(pocket, {x, y, z});
                size_t countActive = countActiveNeighbors(pocket, neighbourgs);

                // std::cout << neighbourgs.size() << std::endl;

                // if (countActive > 0) {
                //     std::cout << "(" << x - int(xSize / 2) << ", " << y - int(ySize / 2) << ", " << z - int(currentCycle) << ")" << std::endl;
                //     for (const State &state : neighbourgs)
                //         std::cout << ((state == ACTIVE) ? "ACTIVE" : "INACTIVE") << std::endl;
                // }

                if (pocket[z][y][x] == '#' && countActive >= 2 && countActive <= 3) {
                    newPocket[z][y][x] = '#';
                } else if (pocket[z][y][x] == '#' && (countActive < 2 || countActive > 3)) {
                    newPocket[z][y][x] = '.';
                } else if (pocket[z][y][x] == '.' && countActive == 3) {
                    newPocket[z][y][x] = '#';
                } else if (pocket[z][y][x] == '.' && countActive != 3) {
                    newPocket[z][y][x] = '.';
                } else {
                    newPocket[z][y][x] = pocket[z][y][x];
                }
            }
        }
    }

    pocket = newPocket;

    compute(pocket, {size.x + 1, size.y + 1}, currentCycle + 1, maxCycle);
}

int main(int ac, char **av)
{
    std::string line;
    std::vector<std::string> initialState;

    while (std::getline(std::cin, line))
        initialState.push_back(line);

    int xSize = initialState[0].size();
    int ySize = initialState.size();
    size_t cycleNumber = (ac == 2) ? std::stoul(av[1]) : 6;

    std::vector<std::vector<std::string>> pocket(cycleNumber * 2 + 1,
        std::vector<std::string>(ySize + (cycleNumber * 2),
            std::string(xSize + (cycleNumber * 2), '.')));

    for (int y = 0; y <= ySize - 1; y++) {
        for (int x = 0; x <= xSize - 1; x++) {
            pocket[cycleNumber][y + ((pocket[0].size() / 2) - (ySize / 2))][x + ((pocket[0][0].size() / 2) - (xSize / 2))] = initialState[y][x];
        }
    }

    compute(pocket, {xSize, ySize}, 0, cycleNumber);

    size_t result = 0;
    for (size_t z = 0; z < pocket.size(); z++)
        for (size_t y = 0; y < pocket[z].size(); y++)
            for (size_t x = 0; x < pocket[z][y].size(); x++)
                if (pocket[z][y][x] == '#')
                    result += 1;

    std::cout << result << std::endl;

    return 0;
}
