#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>

#define BITSTRING_SIZE 36

std::string numberToBitString(size_t number)
{
    std::string result = std::string(BITSTRING_SIZE, '0');

    for (size_t index = 0; number > 0; index++) {
        size_t div = number / 2;
        size_t mod = number % 2;

        result[(BITSTRING_SIZE - 1) - index] = mod + '0';

        number = div;
    }

    return result;
}

size_t bitStringToNumber(std::string bitString)
{
    size_t result = 0;

    for (int index = bitString.size() - 1; index >= 0; index--)
        result += (bitString[index] - '0') * std::pow(2, (bitString.size() - 1) - index);

    return result;
}

void applyMask(std::string &bitString, const std::string &mask)
{
    for (size_t index = 0; index < mask.size(); index++)
        if (mask[index] != '0')
            bitString[index] = mask[index];
}

std::vector<std::string> floatingBitCombinations(const std::string &bitString)
{
    size_t pos = bitString.find('X');
    std::vector<std::string> combinations;

    if (pos != std::string::npos) {
        std::string withZero = bitString;
        withZero[pos] = '0';

        std::vector<std::string> withZeroCombinations =
            floatingBitCombinations(withZero);

        combinations.insert(
            combinations.end(),
            withZeroCombinations.begin(),
            withZeroCombinations.end()
        );

        std::string withOne = bitString;
        withOne[pos] = '1';

        std::vector<std::string> withOneCombinations =
            floatingBitCombinations(withOne);

        combinations.insert(
            combinations.end(),
            withOneCombinations.begin(),
            withOneCombinations.end()
        );
    } else {
        combinations.push_back(bitString);
    }

    return combinations;
}

int main(void)
{
    std::string line;

    std::string mask = std::string(26, 'X');
    std::unordered_map<size_t, size_t> memory;

    while (std::getline(std::cin, line)) {
        std::string prefix = line.substr(0, 4);

        if (prefix == "mask") {
            mask = line.substr(sizeof("mask = ") - 1);
        } else {
            size_t startPos = sizeof("mem[") - 1;
            size_t endPos = line.find(']', startPos);
            std::string index = line.substr(startPos, endPos - startPos);
            std::string value = line.substr(endPos + sizeof(" = "));

            std::string bitString = numberToBitString(std::stoul(index));
            applyMask(bitString, mask);

            std::vector<std::string> combinations = floatingBitCombinations(bitString);
            for (const std::string &combination : combinations)
                memory[bitStringToNumber(combination)] = std::stoul(value);
        }
    }

    size_t result = 0;
    for (auto it = memory.begin(); it != memory.end(); it++)
        result += it->second;

    std::cout << result << std::endl;

    return 0;
}
