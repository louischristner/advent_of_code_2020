#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Group
{
    public:
        Group();

        void addAnswers(const std::string &answers);
        size_t countAnswers(void) const;

    private:
        size_t _groupSize;
        std::unordered_map<char, size_t> _answers;
};

Group::Group(): _groupSize(0)
{
}

void Group::addAnswers(const std::string &answers)
{
    _groupSize += 1;
    for (char c : answers) {
        if (_answers.find(c) == _answers.end()) {
            _answers[c] = 1;
        } else
            _answers[c] += 1;
    }
}

size_t Group::countAnswers(void) const
{
    size_t result = 0;

    for (const std::pair<char, size_t> &p : _answers)
        if (p.second == _groupSize)
            result += 1;

    return result;
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
