#include <vector>
#include <fstream>
#include <iostream>

std::pair<size_t, size_t> getEntries(std::vector<size_t> &numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
        for (size_t j = 0; j < numbers.size(); j++)
            if (numbers[i] + numbers[j] == 2020 && i != j)
                return std::pair<size_t, size_t>(i, j);

    return std::pair<size_t, size_t>(0, 0);
}

int main(void)
{
    std::string line;
    std::vector<size_t> numbers;

    while (std::getline(std::cin, line))
        numbers.push_back(std::stoi(line));

    std::pair<size_t, size_t> entries = getEntries(numbers);

    if (entries.first != entries.second)
        std::cout << numbers[entries.first] * numbers[entries.second] << std::endl;

    return 0;
}
