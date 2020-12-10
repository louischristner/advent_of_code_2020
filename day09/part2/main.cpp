#include <vector>
#include <iostream>
#include <algorithm>

int main(void)
{
    std::string line;
    std::vector<size_t> numbers;
    size_t invalidNumber = 0;

    for (size_t index = 0; std::getline(std::cin, line); index++) {
        numbers.push_back(std::stol(line));

        if (index >= 25) {
            bool isOk = false;
            for (auto itI = numbers.end() - 26; itI != numbers.end() - 1; itI++)
                for (auto itJ = numbers.end() - 26; itJ != numbers.end() - 1; itJ++)
                    if ((*itI) + (*itJ) == *(numbers.end() - 1))
                        isOk = true;

            if (isOk == false) {
                std::cout << *(numbers.end() - 1) << std::endl;
                invalidNumber = *(numbers.end() - 1);
                break;
            }
        }
    }

    for (size_t i = 0; i < numbers.size(); i++) {
        size_t sum = numbers[i];
        size_t lowest = numbers[i];
        size_t highest = numbers[i];
        for (size_t j = i + 1; j < numbers.size(); j++) {
            sum += numbers[j];

            lowest = (numbers[j] < lowest) ? numbers[j] : lowest;
            highest = (numbers[j] > highest) ? numbers[j] : highest;

            if (sum > invalidNumber) {
                break;
            } else if (sum == invalidNumber) {
                std::cout << lowest << " + " << highest << " = " << lowest + highest << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
