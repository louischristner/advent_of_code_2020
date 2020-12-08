#include <vector>
#include <iostream>
#include <algorithm>

class Operation
{
    public:
        Operation(const std::string &name);

        const std::string &getName(void) const;

        void addArg(const std::string &arg);
        const std::vector<std::string> &getArgs(void) const;

        void increaseCount(void);
        const size_t &getCount(void) const;

    protected:
    private:
        size_t _count;
        std::string _name;
        std::vector<std::string> _args;
};

Operation::Operation(const std::string &name):
    _count(0), _name(name)
{
}

const std::string &Operation::getName(void) const
{
    return _name;
}

void Operation::addArg(const std::string &arg)
{
    _args.push_back(arg);
}

const std::vector<std::string> &Operation::getArgs(void) const
{
    return _args;
}

void Operation::increaseCount(void)
{
    _count += 1;
}

const size_t &Operation::getCount(void) const
{
    return _count;
}

int executeOperations(std::vector<Operation> operations)
{
    int index = 0;
    int accumulator = 0;

    while (true) {

        while (index < 0)
            index += operations.size();

        if (index > operations.size())
            break;

        if (operations[index].getCount() > 0)
            break;

        operations[index].increaseCount();
        if (operations[index].getName() == "acc") {
            accumulator += std::stoi(operations[index].getArgs()[0]);
        } else if (operations[index].getName() == "nop") {
            // do nothing
        }

        if (operations[index].getName() == "jmp") {
            index += std::stoi(operations[index].getArgs()[0]);
        } else {
            index += 1;
        }

    }

    return accumulator;
}

int main(void)
{
    std::string line;
    std::vector<Operation> operations;

    while (std::getline(std::cin, line)) {
        size_t splitLine = line.find(' ');

        operations.push_back(Operation(line.substr(0, splitLine)));

        while (true) {
            size_t splitArg = line.find(' ', splitLine + 1);

            (operations.end() - 1)->addArg(line.substr(splitLine + 1, splitArg));
            if (splitArg == std::string::npos)
                break;

            splitLine = splitArg;
        }
    }

    std::cout << executeOperations(operations) << std::endl;

    return 0;
}
