#include <vector>
#include <iostream>
#include <algorithm>

size_t findClosingBracketIndex(const std::string &expression, const size_t &startingPos)
{
    size_t bracketOpenCount = 0;

    for (size_t index = startingPos; index < expression.size(); index++) {
        if (expression[index] == '(') {
            bracketOpenCount += 1;
        } else if (expression[index] == ')') {
            if (bracketOpenCount > 0) {
                bracketOpenCount -= 1;
            } else {
                return index;
            }
        }
    }

    return std::string::npos;
}

size_t computeExpression(std::string expression)
{
    while (true) {
        // std::cout << expression << std::endl;
        size_t posF = expression.find('(');
        if (posF != std::string::npos) {
            size_t posS = findClosingBracketIndex(expression, posF + 1);
            std::string subExpression = expression.substr(posF + 1, posS - (posF + 1));
            std::string computedSubExpression = std::to_string(computeExpression(subExpression));

            expression.replace(posF, posS - (posF - 1), computedSubExpression);
        } else {
            break;
        }
    }

    size_t prevPos = 0;
    std::vector<std::string> members;
    while (true) {
        size_t split = expression.find(' ', prevPos);

        members.push_back(expression.substr(prevPos, split - prevPos));
        if (split == std::string::npos)
            break;

        prevPos = split + 1;
    }

    size_t multSignIndex = 0;
    while (true) {
        for (; multSignIndex < members.size(); multSignIndex++)
            if (members[multSignIndex] == "+")
                break;

        if (multSignIndex != members.size()) {
            size_t result = std::stoul(members[multSignIndex - 1]) + std::stoul(members[multSignIndex + 1]);
            members[multSignIndex - 1] = std::to_string(result);
            members.erase(members.begin() + multSignIndex, members.begin() + multSignIndex + 2);
        } else {
            break;
        }
    }

    while (members.size() > 1) {
        size_t index = 0;
        for (; index < members.size(); index++)
            if (members[index] == "*")
                break;

        size_t result = std::stoul(members[index - 1]) * std::stoul(members[index + 1]);
        members[index - 1] = std::to_string(result);
        members.erase(members.begin() + index, members.begin() + index + 2);
    }

    return std::stoul(members[0]);

    // size_t fNbrSplit = expression.find(' ');

    // if (fNbrSplit != std::string::npos) {
    //     size_t signSplit = expression.find(' ', fNbrSplit + 1);
    //     size_t sNbrSplit = expression.find(' ', signSplit + 1);

    //     std::string fNbr = expression.substr(0, fNbrSplit);
    //     std::string sign = expression.substr(fNbrSplit + 1, signSplit - (fNbrSplit + 1));
    //     std::string sNbr = expression.substr(signSplit + 1, sNbrSplit - (signSplit + 1));

    //     if (sign == "+") {
    //         expression.replace(0, sNbrSplit,
    //             std::to_string(std::stoul(fNbr) + std::stoul(sNbr)));
    //     } else if (sign == "*") {
    //         expression.replace(0, sNbrSplit,
    //             std::to_string(std::stoul(fNbr) * std::stoul(sNbr)));
    //     }

    //     return computeExpression(expression);
    // } else {
    //     return std::stoul(expression);
    // }
}

int main(void)
{
    std::string line;
    std::vector<std::string> expressions;

    while (std::getline(std::cin, line)) {
        expressions.push_back(line);
    }

    size_t result = 0;
    for (size_t index = 0; index < expressions.size(); index++) {
        // std::cout << index << ": " << expressions[index] << std::endl;
        size_t cR = computeExpression(expressions[index]);
        // std::cout << index << ": " << cR << std::endl;
        result += cR;
    }

    std::cout << result << std::endl;

    return 0;
}
