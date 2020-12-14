#include <vector>
#include <iostream>
#include <unordered_map>

size_t getNearestTimestamp(size_t currentTimestamp, size_t id)
{
    size_t result = 0;

    while (result < currentTimestamp)
        result += id;

    return result;
}

int main(void)
{
    std::string line;

    size_t currentTimestamp = 0;
    std::vector<size_t> busIDs;
    std::unordered_map<size_t, size_t> busDeparts;

    for (size_t index = 0; std::getline(std::cin, line); index++) {
        if (index == 0) {
            currentTimestamp = std::stoul(line);
        } else {
            size_t prevIndex = 0;
            while (true) {
                size_t spaceIndex = line.find(',', prevIndex);
                std::string sID = line.substr(prevIndex, spaceIndex - prevIndex);

                if (sID != "x") {
                    size_t id = std::stoul(sID);
                    size_t timestamp =
                        getNearestTimestamp(currentTimestamp, id);

                    busIDs.push_back(id);
                    busDeparts.emplace(id, timestamp);
                }

                if (spaceIndex == std::string::npos)
                    break;
                prevIndex = spaceIndex + 1;
            }
        }
    }

    size_t smallestIndex = busDeparts.begin()->first;
    size_t smallestValue = busDeparts.begin()->second;
    for (auto it = busDeparts.begin(); it != busDeparts.end(); it++) {
        if (smallestValue > it->second) {
                smallestIndex = it->first;
                smallestValue = it->second;
        }
    }

    std::cout << smallestIndex * (smallestValue - currentTimestamp) << std::endl;

    return 0;
}
