#include <vector>
#include <fstream>
#include <iostream>

std::vector<size_t> getEntries(std::vector<size_t> &numbers)
{
    for (size_t i = 0; i < numbers.size(); i++)
        for (size_t j = 0; j < numbers.size(); j++)
            for (size_t k = 0; k < numbers.size(); k++)
                if (numbers[i] + numbers[j] + numbers[k] == 2020 && i != j && j != k)
                    return {i, j, k};

    return {0, 0, 0};
}

int main(void)
{
    std::string line;
    std::vector<size_t> numbers;

    while (std::getline(std::cin, line))
        numbers.push_back(std::stoi(line));

    std::vector<size_t> entries = getEntries(numbers);

    if (entries[0] != entries[1] && entries[1] != entries[2])
        std::cout << numbers[entries[0]] * numbers[entries[1]] * numbers[entries[2]] << std::endl;

    return 0;
}
