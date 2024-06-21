#include <iostream>

#define MAX_LOOP_SIZE 10000000

std::size_t transform(std::size_t subject_number, std::size_t loop_size)
{
    std::size_t value = 1;

    for (std::size_t i = 0; i < loop_size; i++)
        value = (value * subject_number) % 20201227;

    return value;
}

std::size_t transform_while(std::size_t subject_number, std::size_t goal)
{
    std::size_t i = 0;
    std::size_t value = 1;

    for (; i < MAX_LOOP_SIZE && value != goal; i++)
        value = (value * subject_number) % 20201227;

    return i;
}

int main(void)
{
    std::size_t card_public_key = 12090988;
    std::size_t door_public_key = 240583;

    std::size_t card_loop_size = transform_while(7, card_public_key);
    std::size_t door_loop_size = transform_while(7, door_public_key);

    std::cout << "card loop size: " << card_loop_size << " " << transform(door_public_key, card_loop_size) << "\n";
    std::cout << "door loop size: " << door_loop_size << " " << transform(card_public_key, door_loop_size) << "\n";

    return 0;
}