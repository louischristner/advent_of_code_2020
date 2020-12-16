#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct Range
{
    size_t min;
    size_t max;
};

struct Ticket
{
    std::vector<size_t> values;
};

void compute(
    const std::vector<Ticket> &tickets,
    const std::unordered_map<std::string, std::vector<Range>> &fields
)
{
    std::vector<size_t> wrongValues;

    for (const Ticket &ticket : tickets) {
        for (const size_t &val : ticket.values) {
            bool isValid = false;

            for (auto field : fields)
                for (const Range &range : field.second)
                    if (range.min <= val && range.max >= val)
                        isValid = true;

            if (!isValid) {
                wrongValues.push_back(val);
            }

        }
    }

    size_t result = 0;
    for (const size_t &val : wrongValues)
        result += val;

    std::cout << result << std::endl;
}

int main(void)
{
    Ticket myTicket;
    std::vector<Ticket> tickets;
    std::unordered_map<std::string, std::vector<Range>> fields;

    size_t part = 0;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            part += 1;
        } else if (part == 0) {

            size_t pos = line.find(": ");
            std::string fieldName = line.substr(0, pos);

            size_t posOr = line.find("or", pos);
            std::string firstField = line.substr(pos + 2, posOr - (pos + 2));
            std::string secondField = line.substr(posOr + 3);

            size_t posFirstSplit = firstField.find('-');
            size_t posSecondSplit = secondField.find('-');

            fields[fieldName].push_back({
                std::stoul(firstField.substr(0, posFirstSplit)),
                std::stoul(firstField.substr(posFirstSplit + 1))
            });

            fields[fieldName].push_back({
                std::stoul(secondField.substr(0, posSecondSplit)),
                std::stoul(secondField.substr(posSecondSplit + 1))
            });

        } else if (part == 1 && line != "your ticket:") {

            size_t prevPos = 0;
            while (true) {
                size_t pos = line.find(',', prevPos);
                std::string value = line.substr(prevPos, pos - prevPos);

                myTicket.values.push_back(std::stoul(value));

                if (pos == std::string::npos)
                    break;

                prevPos = pos + 1;
            }

        } else if (part == 2 && line != "nearby tickets:") {

            tickets.push_back(Ticket());

            size_t prevPos = 0;
            while (true) {
                size_t pos = line.find(',', prevPos);
                std::string value = line.substr(prevPos, pos - prevPos);

                tickets[tickets.size() - 1].values.push_back(std::stoul(value));

                if (pos == std::string::npos)
                    break;

                prevPos = pos + 1;
            }
        }
    }

    compute(tickets, fields);

    return 0;
}
