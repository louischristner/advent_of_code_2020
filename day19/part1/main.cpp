#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Rule
{
    char c;
    std::vector<std::vector<size_t>> rules;
};

std::vector<std::string> parseLine(const std::string &line, char sign, size_t prevPos, size_t incrementor)
{
    std::vector<std::string> lines;

    while (true) {
        size_t pos = line.find(sign, prevPos);
        lines.push_back(line.substr(prevPos, pos - prevPos));
        if (pos == std::string::npos)
            break;
        prevPos = pos + incrementor;
    }

    return lines;
}

void getArgs(std::unordered_map<size_t, Rule> &rules, std::vector<std::string> &messages)
{
    std::string line;

    for (size_t index = 0; std::getline(std::cin, line); ) {
        if (line.empty()) {
            index += 1;
        } else if (index == 0) {
            size_t splitIndex = line.find(':');
            size_t index = std::stoi(line.substr(0, splitIndex));

            size_t prevPos = splitIndex + 2;
            std::vector<std::string> lines =
                parseLine(line, '|', prevPos, 2);

            if (lines.size() == 1 && lines[0][0] == '"') {
                rules.insert(std::pair<size_t, Rule>(index, {lines[0][1], {}}));
            } else {
                rules.insert(std::pair<size_t, Rule>(index, {'\0', {}}));
                for (const auto &l : lines) {
                    auto sLines = parseLine(l, ' ', 0, 1);

                    std::vector<size_t> oRules;
                    for (const auto &sL : sLines)
                        if (!sL.empty())
                            oRules.push_back(std::stoi(sL));
                    rules[index].rules.push_back(oRules);
                }
            }
        } else {
            messages.push_back(line);
        }
    }
}

bool computeMessage(std::unordered_map<size_t, Rule> &rules, const std::string &message, const size_t index, size_t &mIndex)
{
    if (rules[index].rules.size() > 0) {
        for (size_t i = 0; i < rules[index].rules.size(); i++) {

            size_t tmpMIndex = mIndex;
            std::vector<bool> validRules;

            for (size_t j = 0; j < rules[index].rules[i].size(); j++) {
                bool isValid = computeMessage(rules, message, rules[index].rules[i][j], tmpMIndex);

                validRules.push_back(isValid);
                if (rules[rules[index].rules[i][j]].rules.size() == 0 && isValid) {
                    // std::cout << rules[index].rules[i][j] << " " << tmpMIndex << std::endl;
                    tmpMIndex += 1;
                }
            }

            if (std::find(validRules.begin(), validRules.end(), false) == validRules.end()) {
                mIndex = tmpMIndex;
                return true;
            }
        }
    } else {
        return (rules[index].c == message[mIndex]);
    }

    return false;
}

void compute(std::unordered_map<size_t, Rule> &rules, const std::vector<std::string> &messages)
{
    size_t result = 0;

    for (const auto &message : messages) {
        size_t mIndex = 0;
        if (computeMessage(rules, message, 0, mIndex) && mIndex == message.size()) {
            std::cout << message << " is valid" << std::endl;
            result += 1;
        }
    }

    std::cout << result << std::endl;
}

int main(void)
{
    std::vector<std::string> messages;
    std::unordered_map<size_t, Rule> rules;

    getArgs(rules, messages);
    compute(rules, messages);

    return 0;
}
