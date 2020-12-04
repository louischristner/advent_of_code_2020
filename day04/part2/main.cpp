#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

bool byrValidator(const std::string &byr)
{
    return (
        byr.size() == 4 &&
        std::all_of(byr.begin(), byr.end(), [](char c){return std::isdigit(c);}) &&
        std::stoi(byr) >= 1920 && std::stoi(byr) <= 2002
    );
}

bool iyrValidator(const std::string &iyr)
{
    return (
        iyr.size() == 4 &&
        std::all_of(iyr.begin(), iyr.end(), [](char c){return std::isdigit(c);}) &&
        std::stoi(iyr) >= 2010 && std::stoi(iyr) <= 2020
    );
}

bool eyrValidator(const std::string &eyr)
{
    return (
        eyr.size() == 4 &&
        std::all_of(eyr.begin(), eyr.end(), [](char c){return std::isdigit(c);}) &&
        std::stoi(eyr) >= 2020 && std::stoi(eyr) <= 2030
    );
}

bool hgtValidator(const std::string &hgt)
{
    std::string nbr = hgt.substr(0, hgt.size() - 2);
    std::string sub = hgt.substr(hgt.size() - 2);

    if (nbr.empty())
        return false;
    if (sub.empty())
        return false;

    return (
        std::all_of(nbr.begin(), nbr.end(), [](char c){return std::isdigit(c);}) &&
        (sub == "cm" || sub == "in") &&
        (sub == "cm")
            ? std::stoi(nbr) >= 150 && std::stoi(nbr) <= 193
            : std::stoi(nbr) >= 59 && std::stoi(nbr) <= 76
    );
}

bool hclValidator(const std::string &hcl)
{
    return (
        hcl[0] == '#' &&
        hcl.size() == 7 &&
        std::all_of(hcl.begin() + 1, hcl.end(), [](char c){return std::isdigit(c) || (c >= 'a' && c <= 'f');})
    );
}

bool eclValidator(const std::string &ecl)
{
    const std::string colors[] = {
        "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
    };

    return (
        std::find(std::begin(colors), std::end(colors), ecl) != std::end(colors)
    );
}

bool pidValidator(const std::string &pid)
{
    return (
        pid.size() == 9 &&
        std::all_of(pid.begin(), pid.end(), [](char c){return std::isdigit(c);})
    );
}

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

    bool (*requiredFuncPointers[])(const std::string &) = {
        &byrValidator,
        &iyrValidator,
        &eyrValidator,
        &hgtValidator,
        &hclValidator,
        &eclValidator,
        &pidValidator
    };

    for (size_t index = 0; index < sizeof(requireds) / sizeof(requireds[0]); index++) {
        if (_fields.find(requireds[index]) == _fields.end()) {
            return false;
        } else {
            if (!requiredFuncPointers[index](_fields[requireds[index]]))
                return false;
        }
    }

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
