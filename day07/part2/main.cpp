#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Bag
{
    Bag(const std::string &name): name(name)
    {}

    std::string name;
    std::unordered_map<std::string, size_t> bags;
};

// size_t checkIfBagContainsWanted(const std::string &wanted, const Bag &bag, const std::vector<Bag> &bags, const size_t index)
// {
//     // std::cout << std::string(index, '\t') << " - " << bag.name << std::endl;

//     if (bag.name == wanted)
//         return 1;

//     if (bag.bags.size() == 0)
//         return 0;

//     for (const std::string &bagName : bag.bags)
//         for (const Bag &ibag : bags)
//             if (ibag.name == bagName)
//                 if (checkIfBagContainsWanted(wanted, ibag, bags, index + 1))
//                     return 1;

//     return 0;
// }

int countBagInsideWanted(const Bag &bag, const std::vector<Bag> &bags, const size_t index)
{
    size_t result = 0;

    if (bag.bags.size() == 0)
        return -1;

    for (const std::pair<std::string, size_t> &bagName : bag.bags) {

        int inResult = 0;
        for (const Bag &ibag : bags)
            if (ibag.name == bagName.first)
                inResult = countBagInsideWanted(ibag, bags, index + 1);

        if (inResult == -1) {
            result += bagName.second;
        } else {
            result += (bagName.second + (bagName.second * inResult));
        }

    }

    return result;
}

int main(void)
{
    std::string line;
    std::vector<Bag> bags;

    while (std::getline(std::cin, line)) {
        std::string splitter = " bags contain ";
        size_t splitPos = line.find(splitter);
        std::string mainBag = line.substr(0, splitPos);

        bags.push_back(Bag(mainBag));

        while (true) {
            size_t bagPos = line.find(",", splitPos);
            std::string insideBag = line.substr(splitPos + splitter.size(), bagPos - (splitPos + splitter.size()));
            if (insideBag == "no other bags.")
                break;

            size_t numPos = insideBag.find(" ");
            size_t subPos = insideBag.find(" bag");
            std::string bagColor = insideBag.substr(numPos + 1, subPos - (numPos + 1));

            (bags.end() - 1)->bags[bagColor] = std::stoi(insideBag.substr(0, numPos));

            if (bagPos == std::string::npos)
                break;

            splitter = ",";
            splitPos = bagPos + 1;
        }
    }

    std::vector<Bag>::iterator itBag = std::find_if(bags.begin(), bags.end(), [](const Bag &bag){
        return bag.name == "shiny gold";
    });

    std::cout << countBagInsideWanted(*itBag, bags, 0) << std::endl;

    return 0;
}
