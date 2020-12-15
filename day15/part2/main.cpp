#include <vector>
#include <iostream>
#include <algorithm>

size_t compute(const std::vector<size_t> &startingNumbers, const size_t wantedIndex)
{
    size_t turn = 1;
    size_t last = 0;
    std::vector<size_t> numbers(wantedIndex);

    std::for_each(startingNumbers.begin(), std::prev(startingNumbers.end()), [&](size_t nbr){
        numbers[nbr] = turn;
        turn++;
    });

    last = startingNumbers.back();

    for (; turn < wantedIndex; turn++) {
        size_t next = (numbers[last] == 0)
            ? 0 : turn - numbers[last];
        numbers[last] = turn;
        last = next;
    }

    return last;
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

    std::cout << compute(startingNumbers, 30000000) << std::endl;

    return 0;
}
