#include <vector>
#include <iostream>
#include <unordered_map>

struct Bus
{
    size_t id;
    size_t index;
};

size_t getNearestTimestamp(size_t currentTimestamp, size_t id)
{
    size_t result = 0;

    while (result < currentTimestamp)
        result += id;

    return result;
}

size_t getHighestTimestamp(std::vector<size_t> timestamps)
{
    size_t result = 0;

    for (size_t index = 0; index < timestamps.size(); index++)
        if (timestamps[index] > result)
            result = timestamps[index];

    return result;
}

int main(void)
{
    std::string line;
    std::vector<Bus> busVector;

    for (size_t index = 0; std::getline(std::cin, line); index++) {
        if (index > 0) {
            size_t prevIndex = 0;
            for (size_t index = 0; true; index++) {
                size_t spaceIndex = line.find(',', prevIndex);
                std::string sID = line.substr(prevIndex, spaceIndex - prevIndex);

                if (sID != "x") {
                    size_t id = std::stoul(sID);
                    busVector.push_back({id, index});
                }

                if (spaceIndex == std::string::npos)
                    break;
                prevIndex = spaceIndex + 1;
            }
        }
    }

    /* SEPARATION */

    std::vector<size_t> timestamps;
    for (Bus bus : busVector)
        timestamps.push_back(bus.id);

    while (true) {
        size_t highestValue = getHighestTimestamp(timestamps);

        for (size_t index = 0; index < timestamps.size(); index++)
            timestamps[index] =
                getNearestTimestamp(highestValue, busVector[index].id);

        std::cout << highestValue << std::endl;
        // for (size_t timestamp : timestamps)
        //     std::cout << timestamp << std::endl;

        bool isValid = true;
        for (size_t index = 0; index < timestamps.size(); index++)
            if (timestamps[index] - timestamps[0] != busVector[index].index)
                isValid = false;

        if (isValid)
            break;
    }

    return 0;
}
