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

    size_t fNbrSplit = expression.find(' ');

    if (fNbrSplit != std::string::npos) {
        size_t signSplit = expression.find(' ', fNbrSplit + 1);
        size_t sNbrSplit = expression.find(' ', signSplit + 1);

        std::string fNbr = expression.substr(0, fNbrSplit);
        std::string sign = expression.substr(fNbrSplit + 1, signSplit - (fNbrSplit + 1));
        std::string sNbr = expression.substr(signSplit + 1, sNbrSplit - (signSplit + 1));

        if (sign == "+") {
            expression.replace(0, sNbrSplit,
                std::to_string(std::stoul(fNbr) + std::stoul(sNbr)));
        } else if (sign == "*") {
            expression.replace(0, sNbrSplit,
                std::to_string(std::stoul(fNbr) * std::stoul(sNbr)));
        }

        return computeExpression(expression);
    } else {
        return std::stoul(expression);
    }
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
