#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

size_t factorial(size_t v)
{
    return (v == 0 || v == 1) ? 1 : v * factorial(v - 1);
}

std::vector<size_t> getRemovablesWithoutValues(const std::vector<size_t> &adapters, std::vector<size_t> values = {})
{
    std::vector<size_t> removables;
    std::vector<size_t> cpyAdapters;

    std::copy_if(
        adapters.begin(),
        adapters.end(),
        std::back_inserter(cpyAdapters),
        [values](const size_t &adapter){
            return (std::find(values.begin(), values.end(), adapter) == values.end());
        }
    );

    for (auto it = cpyAdapters.begin() + 1; it != cpyAdapters.end() - 1; it++) {
        if ((*(it + 1)) - (*(it - 1)) <= 3) {
            std::cout << ((removables.size() == 0) ? "" : ", ") << *it;
            removables.push_back(*it);
        }
    }

    std::cout << std::endl;
    return removables;
}

void arrangeAdapters(const std::vector<size_t> &adapters)
{
    std::vector<size_t> removables =
        getRemovablesWithoutValues(adapters);

    size_t rSize = removables.size();
    size_t rPow = std::pow(2, rSize);

    std::cout << rPow << std::endl;
}

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

    arrangeAdapters(adapters);

    return 0;
}
