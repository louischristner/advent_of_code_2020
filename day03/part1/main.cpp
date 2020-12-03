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

    std::cout << compute(3, 1, lines) << std::endl;

    return 0;
}
