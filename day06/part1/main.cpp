#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Group
{
    public:
        Group() = default;

        void addAnswers(const std::string &answers);
        size_t countAnswers(void) const;

    private:
        std::unordered_map<char, size_t> _answers;
};

void Group::addAnswers(const std::string &answers)
{
    for (char c : answers) {
        if (_answers.find(c) == _answers.end()) {
            _answers[c] = 1;
        } else
            _answers[c] += 1;
    }
}

size_t Group::countAnswers(void) const
{
    return _answers.size();
}

int main(void)
{
    std::string line;
    std::vector<Group> groups;

    while (std::getline(std::cin, line)) {
        if (groups.size() == 0)
            groups.push_back(Group());

        if (line.empty()) {
            groups.push_back(Group());
        } else {
            (groups.end() - 1)->addAnswers(line);
        }
    }

    size_t result = 0;
    for (const Group &group : groups)
        result += group.countAnswers();

    std::cout << result << std::endl;

    return 0;
}
