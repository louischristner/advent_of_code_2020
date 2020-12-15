#include <vector>
#include <iostream>

int findBackwardFromIndex(const std::vector<size_t> &numbers, const size_t wanted, int index)
{
    for (; index >= 0 && index < numbers.size(); index--)
        if (numbers[index] == wanted)
            break;

    return index;
}

size_t compute(const std::vector<size_t> &startingNumbers, const size_t wantedIndex)
{
    size_t index = 0;
    std::vector<size_t> numbers;

    for (; index < wantedIndex; index++) {
        if (index < startingNumbers.size()) {
            numbers.push_back(startingNumbers[index]);
        } else {
            int findNearest = findBackwardFromIndex(numbers, numbers[index - 1], index - 2);
            if (findNearest < 0) {
                numbers.push_back(0);
            } else {
                numbers.push_back(index - (findNearest + 1));
            }
        }
    }

    return numbers[index - 1];
}

int main(void)
{
    std::string line;
    std::vector<size_t> startingNumbers;

    while (std::getline(std::cin, line)) {
        size_t prevPos = 0;

        while (true) {
            size_t pos = line.find(',', prevPos);
            std::string sNbr = line.substr(prevPos, pos - prevPos);

            startingNumbers.push_back(std::stoul(sNbr));

            if (pos == std::string::npos)
                break;

            prevPos = pos + 1;
        }
    }

    std::cout << compute(startingNumbers, 2020) << std::endl;

    return 0;
}
