#include <vector>
#include <iostream>
#include <algorithm>

struct PasswordPolicy
{
    size_t min;
    size_t max;
    char symbol;
};

class Password
{
    public:
        Password(std::string password, PasswordPolicy passwordPolicy);

        bool isValid(void);

    private:
        std::string _password;
        PasswordPolicy _passwordPolicy;
};

Password::Password(std::string password, PasswordPolicy passwordPolicy):
    _password(password), _passwordPolicy(passwordPolicy) {}

bool Password::isValid(void)
{
    return (_password[_passwordPolicy.min - 1] == _passwordPolicy.symbol || _password[_passwordPolicy.max - 1] == _passwordPolicy.symbol) && _password[_passwordPolicy.min - 1] != _password[_passwordPolicy.max - 1];
}

int main(void)
{
    std::string line;
    std::vector<Password> passwords;
    size_t countValid = 0;

    while (std::getline(std::cin, line)) {
        size_t firstS = line.find(' ');
        size_t secondS = line.find(' ', firstS + 1);

        std::string limits = line.substr(0, firstS);
        size_t thirdS = limits.find('-');

        passwords.push_back(
            Password(line.substr(secondS + 1),
            {
                static_cast<size_t>(std::stoi(limits.substr(0, thirdS))),
                static_cast<size_t>(std::stoi(limits.substr(thirdS + 1))),
                line[firstS + 1]
            })
        );
    }

    for (auto password : passwords)
        if (password.isValid())
            countValid += 1;

    std::cout << countValid << std::endl;

    return 0;
}
