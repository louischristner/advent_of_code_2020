#include <vector>
#include <iostream>
#include <algorithm>

size_t narrowRows(const std::string &seat, const size_t index, const size_t min, const size_t max)
{
    if (seat[index] == 'F') {
        return narrowRows(seat, index + 1, min, ((max - min) / 2) + min);
    } else if (seat[index] == 'B') {
        return narrowRows(seat, index + 1, ((max - min) / 2) + min + 1, max);
    } else {
        return (min + max) / 2;
    }
}

size_t narrowColumns(const std::string &seat, const size_t index, const size_t min, const size_t max)
{
    if (seat.size() <= index)
        return (min + max) / 2;

    if (seat[index] == 'L') {
        return narrowColumns(seat, index + 1, min, ((max - min) / 2) + min);
    } else if (seat[index] == 'R') {
        return narrowColumns(seat, index + 1, ((max - min) / 2) + min + 1, max);
    } else {
        return narrowColumns(seat, index + 1, min, max);
    }
}

int main(void)
{
    std::string line;
    std::vector<size_t> seatsId;

    while (std::getline(std::cin, line)) {
        size_t rows = narrowRows(line, 0, 0, 127);
        size_t cols = narrowColumns(line, 0, 0, 7);

        seatsId.push_back(rows * 8 + cols);
    }

    std::sort(seatsId.begin(), seatsId.end());

    size_t prevSeat = seatsId[0];
    for (size_t index = 1; index < seatsId.size(); index++) {
        if (seatsId[index] != prevSeat + 1)
            std::cout << prevSeat + 1 << std::endl;
        prevSeat = seatsId[index];
        // std::cout << seatId << std::endl;
    }

    return 0;
}
