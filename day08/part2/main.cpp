#include <vector>
#include <iostream>
#include <algorithm>

class Operation
{
    public:
        Operation(const std::string &name);

        void setName(const std::string name);
        const std::string &getName(void) const;

        void addArg(const std::string &arg);
        const std::vector<std::string> &getArgs(void) const;

        void increaseCount(void);
        void setCount(const size_t count);
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

void Operation::setName(const std::string name)
{
    _name = name;
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

void Operation::setCount(const size_t count)
{
    _count = count;
}

const size_t &Operation::getCount(void) const
{
    return _count;
}

bool executeOperations(int &accumulator, std::vector<Operation> operations)
{
    int index = 0;

    while (true) {

        while (index < 0)
            index += operations.size();

        if (index > operations.size())
            break;

        if (operations[index].getCount() > 0)
            return false;

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

    return true;
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

    int accumulator = 0;

    for (int index = 0; index < operations.size(); index++) {
        if (operations[index].getName() == "jmp") {
            operations[index].setName("nop");
            if (executeOperations(accumulator, operations))
                std::cout << accumulator << std::endl;
            operations[index].setName("jmp");
            accumulator = 0;
        } else if (operations[index].getName() == "nop") {
            operations[index].setName("jmp");
            if (executeOperations(accumulator, operations))
                std::cout << accumulator << std::endl;
            operations[index].setName("nop");
            accumulator = 0;
        }
    }

    return 0;
}
