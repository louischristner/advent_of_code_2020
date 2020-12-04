#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class Passport
{
    public:
        Passport() = default;

        bool isValid(void);
        void getDataFromString(const std::string &data);

    private:
        std::unordered_map<std::string, std::string> _fields;
};

bool Passport::isValid(void)
{
    const std::string requireds[] = {
        "byr", // Birth Year
        "iyr", // Issue Year
        "eyr", // Expiration Year
        "hgt", // Height
        "hcl", // Hair Color
        "ecl", // Eye Color
        "pid" // Passport ID
    };

    for (size_t index = 0; index < sizeof(requireds) / sizeof(requireds[0]); index++)
        if (_fields.find(requireds[index]) == _fields.end())
            return false;

    return true;
}

void Passport::getDataFromString(const std::string &data)
{
    size_t prevPos = 0;

    while (true) {
        size_t spacePos = data.find(' ', prevPos);

        std::string sub = data.substr(prevPos, spacePos - prevPos);

        size_t splitPos = sub.find(':');
        std::string key = sub.substr(0, splitPos);
        std::string val = sub.substr(splitPos + 1);
        _fields[key] = val;

        if (spacePos == std::string::npos)
            break;

        prevPos = spacePos + 1;
    }
}

int main(void)
{
    std::string line;
    std::vector<Passport> passports;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            passports.push_back(Passport());
        } else {
            if (passports.size() == 0)
                passports.push_back(Passport());
            (passports.end() - 1)->getDataFromString(line);
        }
    }

    size_t countValid = std::count_if(passports.begin(), passports.end(), [](Passport &passport){
        return passport.isValid();
    });

    std::cout << countValid << std::endl;

    return 0;
}
