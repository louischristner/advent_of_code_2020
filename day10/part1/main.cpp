#include <vector>
#include <iostream>
#include <algorithm>

int main(void)
{
    std::string line;
    std::vector<size_t> adapters;
    size_t highestRatedAdapter = 0;

    adapters.push_back(0);
    while (std::getline(std::cin, line))
        adapters.push_back(std::stoul(line));

    std::sort(adapters.begin(), adapters.end());

    highestRatedAdapter = *(adapters.end() - 1);
    adapters.push_back(highestRatedAdapter + 3);

    size_t differences[3] = {0};

    for (auto it = adapters.begin() + 1; it != adapters.end(); it++)
        differences[((*it) - (*(it - 1)) - 1)] += 1;

    std::cout << differences[0] << std::endl;
    std::cout << differences[1] << std::endl;
    std::cout << differences[2] << std::endl;

    std::cout << differences[0] << " * " << differences[2] << " = " << differences[0] * differences[2] << std::endl;

    return 0;
}
