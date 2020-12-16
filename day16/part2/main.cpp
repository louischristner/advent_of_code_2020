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
    bool isValid;
    std::vector<size_t> values;
};

void compute(
    std::vector<Ticket> tickets,
    const std::unordered_map<std::string, std::vector<Range>> &fields
)
{
    for (Ticket &ticket : tickets) {
        for (const size_t &val : ticket.values) {
            bool isValid = false;

            for (auto field : fields)
                for (const Range &range : field.second)
                    if (range.min <= val && range.max >= val)
                        isValid = true;

            if (!isValid) {
                ticket.isValid = false;
            }

        }
    }

    auto removeIt = std::remove_if(tickets.begin(), tickets.end(), [](const Ticket &ticket){
        return (!ticket.isValid);
    });

    tickets.erase(removeIt, tickets.end());

    std::vector<std::vector<std::vector<size_t>>> fieldsPossibilities(
        tickets.size(), std::vector<std::vector<size_t>>(
            fields.size(), std::vector<size_t>()));

    for (size_t i = 0; i < tickets.size(); i++) {
        for (size_t j = 0; j < tickets[i].values.size(); j++) {

            size_t k = 0;
            for (auto field : fields) {
                if ((field.second[0].min <= tickets[i].values[j] && field.second[0].max >= tickets[i].values[j]) ||
                    (field.second[1].min <= tickets[i].values[j] && field.second[1].max >= tickets[i].values[j])) {
                    fieldsPossibilities[i][j].push_back(k);
                }

                k += 1;
            }
        }
    }

    // size_t index = 0;
    // for (auto fieldPossibilities : fieldsPossibilities) {
    //     std::cout << index << std::endl;

    //     size_t iIndex = 0;
    //     for (auto fieldPossibility : fieldPossibilities) {
    //         std::cout << " - " << iIndex << " " << fieldPossibility.size() << std::endl;
    //         // for (auto possibility : fieldPossibility)
    //         //     std::cout << " - " << possibility << std::endl;
    //         // iIndex += 1;
    //     }

    //     index += 1;
    // }

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

            myTicket.isValid = true;

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
            tickets[tickets.size() - 1].isValid = true;

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
