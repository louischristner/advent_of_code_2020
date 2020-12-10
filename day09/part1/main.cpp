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
                invalidNumber = *(numbers.end() - 1);
                break;
            }
        }
    }

    std::cout << invalidNumber << std::endl;

    return 0;
}
