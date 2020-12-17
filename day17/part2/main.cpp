#include <vector>
#include <iostream>
#include <algorithm>

struct Vect2D
{
    int x;
    int y;
};

struct Vect4D
{
    int x;
    int y;
    int z;
    int w;
};

enum State
{
    ACTIVE,
    INACTIVE
};

void display(const std::vector<std::vector<std::vector<std::string>>> &pocket, Vect2D size, size_t currentCycle, size_t maxCycle)
{
    std::cout << ((currentCycle == 0) ? "Before any cycle" : "After " + std::to_string(currentCycle) + " cycle") << std::endl;

    for (int w = 0; w < pocket.size(); w++) {
        for (int z = 0; z < pocket[w].size(); z++) {
            bool hasActiveCell = false;
            for (int y = 0; y < pocket[w][z].size(); y++)
                for (int x = 0; x < pocket[w][z][y].size(); x++)
                    if (pocket[w][z][y][x] == '#')
                        hasActiveCell = true;

            if (!hasActiveCell)
                continue;

            std::cout << std::endl << "z=" << z << ", w=" << w << std::endl;

            for (int y = 0; y < pocket[w][z].size(); y++) {
                for (int x = 0; x < pocket[w][z][y].size(); x++)
                    std::cout << pocket[w][z][y][x];
                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;
}

size_t countActiveNeighbors(const std::vector<std::vector<std::vector<std::string>>> &pocket, const std::vector<Vect4D> &neighbors)
{
    size_t result = 0;
    size_t wSize = pocket.size();
    size_t zSize = pocket[0].size();
    size_t ySize = pocket[0][0].size();
    size_t xSize = pocket[0][0][0].size();

    for (const Vect4D &neighbor : neighbors)
        if (neighbor.x >= 0 && neighbor.y >= 0 && neighbor.z >= 0 && neighbor.w >= 0 && neighbor.x <= xSize - 1 && neighbor.y <= ySize - 1 && neighbor.z <= zSize - 1 && neighbor.w <= wSize - 1)
            if (pocket[neighbor.w][neighbor.z][neighbor.y][neighbor.x] == '#')
                result += 1;

    return result;
}

std::vector<Vect4D> getNeighbors(const std::vector<std::vector<std::vector<std::string>>> &pocket, const Vect4D pos)
{
    std::vector<Vect4D> neighbors;

    for (int w = pos.w - 1; w <= pos.w + 1; w++)
        for (int z = pos.z - 1; z <= pos.z + 1; z++)
            for (int y = pos.y - 1; y <= pos.y + 1; y++)
                for (int x = pos.x - 1; x <= pos.x + 1; x++)
                    if (x != pos.x || y != pos.y || z != pos.z || w != pos.w)
                        neighbors.push_back({x, y, z, w});

    return neighbors;
}

void compute(std::vector<std::vector<std::vector<std::string>>> &pocket, Vect2D size, size_t currentCycle, size_t maxCycle)
{
    display(pocket, size, currentCycle, maxCycle);
    if (currentCycle == maxCycle)
        return;

    size_t wSize = pocket.size();
    size_t zSize = pocket[0].size();
    size_t ySize = pocket[0][0].size();
    size_t xSize = pocket[0][0][0].size();
    std::vector<std::vector<std::vector<std::string>>> newPocket = pocket;

    for (int w = 0; w < wSize; w++) {
        for (int z = 0; z < zSize; z++) {
            for (int y = 0; y < ySize; y++) {
                for (int x = 0; x < xSize; x++) {
                    std::vector<Vect4D> neighbourgs = getNeighbors(pocket, {x, y, z, w});
                    size_t countActive = countActiveNeighbors(pocket, neighbourgs);

                    if (pocket[w][z][y][x] == '#' && countActive >= 2 && countActive <= 3) {
                        newPocket[w][z][y][x] = '#';
                    } else if (pocket[w][z][y][x] == '#' && (countActive < 2 || countActive > 3)) {
                        newPocket[w][z][y][x] = '.';
                    } else if (pocket[w][z][y][x] == '.' && countActive == 3) {
                        newPocket[w][z][y][x] = '#';
                    } else if (pocket[w][z][y][x] == '.' && countActive != 3) {
                        newPocket[w][z][y][x] = '.';
                    } else {
                        newPocket[w][z][y][x] = pocket[w][z][y][x];
                    }
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

    std::vector<std::vector<std::vector<std::string>>> pocket(cycleNumber * 4 + 1,
        std::vector<std::vector<std::string>>(cycleNumber * 4 + 1,
            std::vector<std::string>(ySize + (cycleNumber * 4),
                std::string(xSize + (cycleNumber * 4), '.'))));

    for (int y = 0; y <= ySize - 1; y++) {
        for (int x = 0; x <= xSize - 1; x++) {
            pocket[cycleNumber][cycleNumber][y + ((pocket[0].size() / 2) - (ySize / 2))][x + ((pocket[0][0].size() / 2) - (xSize / 2))] = initialState[y][x];
        }
    }

    compute(pocket, {xSize, ySize}, 0, cycleNumber);

    size_t result = 0;
    for (size_t w = 0; w < pocket.size(); w++)
        for (size_t z = 0; z < pocket[w].size(); z++)
            for (size_t y = 0; y < pocket[w][z].size(); y++)
                for (size_t x = 0; x < pocket[w][z][y].size(); x++)
                    if (pocket[w][z][y][x] == '#')
                        result += 1;

    std::cout << result << std::endl;

    return 0;
}
