#include <vector>
#include <iostream>
#include <algorithm>

size_t compute(size_t x, size_t y, std::vector<std::string> lines)
{
    size_t count = 0;

    size_t xSize = lines[0].size();
    size_t ySize = lines.size();

    size_t xIndex = 0;
    size_t yIndex = 0;

    while (yIndex < ySize) {
        if (lines[yIndex][xIndex] == '#')
            count += 1;
        xIndex = (xIndex + x) % xSize;
        yIndex += y;
    }

    return count;
}

int main(void)
{
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(std::cin, line))
        lines.push_back(line);

    std::pair<size_t, size_t> indexes[5] = {
        {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}
    };

    for (auto index : indexes)
        std::cout << compute(index.first, index.second, lines) << std::endl;

    return 0;
}
