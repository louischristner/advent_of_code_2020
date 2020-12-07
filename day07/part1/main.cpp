#include <vector>
#include <iostream>
#include <algorithm>

struct Bag
{
    Bag(const std::string &name): name(name)
    {}

    std::string name;
    std::vector<std::string> bags;
};

size_t checkIfBagContainsWanted(const std::string &wanted, const Bag &bag, const std::vector<Bag> &bags, const size_t index)
{
    // std::cout << std::string(index, '\t') << " - " << bag.name << std::endl;

    if (bag.name == wanted)
        return 1;

    if (bag.bags.size() == 0)
        return 0;

    for (const std::string &bagName : bag.bags)
        for (const Bag &ibag : bags)
            if (ibag.name == bagName)
                if (checkIfBagContainsWanted(wanted, ibag, bags, index + 1))
                    return 1;

    return 0;
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

            (bags.end() - 1)->bags.push_back(bagColor);

            if (bagPos == std::string::npos)
                break;

            splitter = ",";
            splitPos = bagPos + 1;
        }
    }

    size_t result = 0;
    for (const Bag &bag : bags)
        if (bag.name != "shiny gold")
            result += checkIfBagContainsWanted("shiny gold", bag, bags, 0);

    std::cout << result << std::endl;

    return 0;
}
