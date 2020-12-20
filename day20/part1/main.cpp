#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#define SQUARE_SIZE 10

class Square
{
    public:
        Square(size_t id);

        void flipX(void);
        void flipY(void);
        void rotate(void);
        void display(void) const;
        const size_t &getId() const;
        void addSquareLine(const std::string &line);
        void setSquare(const std::vector<char> &square);

        const char &operator[](size_t y) const;

    private:
        size_t _id;
        std::vector<char> _square;
};

Square::Square(size_t id): _id(id), _square(SQUARE_SIZE * SQUARE_SIZE, '\0')
{
}

void Square::flipX(void)
{
    std::vector<char> newSquare(SQUARE_SIZE * SQUARE_SIZE, '\0');

    for (size_t y = 0; y < SQUARE_SIZE; y++)
        for (size_t x = 0; x < SQUARE_SIZE; x++)
            newSquare[x + (y * SQUARE_SIZE)] = _square[x + (((SQUARE_SIZE - 1) - y) * SQUARE_SIZE)];

    setSquare(newSquare);
}

void Square::flipY(void)
{
    std::vector<char> newSquare(SQUARE_SIZE * SQUARE_SIZE, '\0');

    for (size_t y = 0; y < SQUARE_SIZE; y++)
        for (size_t x = 0; x < SQUARE_SIZE; x++)
            newSquare[x + (y * SQUARE_SIZE)] = _square[((SQUARE_SIZE - 1) - x) + (y * SQUARE_SIZE)];

    setSquare(newSquare);
}

void Square::rotate(void)
{
    size_t xCol = 0;
    size_t yRow = SQUARE_SIZE - 1;
    std::vector<char> newSquare(SQUARE_SIZE * SQUARE_SIZE, '\0');

    for (; xCol < SQUARE_SIZE; xCol++, yRow--)
        for (size_t i = 0; i < SQUARE_SIZE; i++)
            newSquare[i + (yRow * SQUARE_SIZE)] = _square[xCol + (i * SQUARE_SIZE)];

    setSquare(newSquare);
}

void Square::display(void) const
{
    std::cout << "Tile " << _id << ":" << std::endl;
    for (size_t y = 0; y < SQUARE_SIZE; y++)
        for (size_t x = 0; x < SQUARE_SIZE; x++)
            std::cout << _square[x + y * SQUARE_SIZE] << ((x + 1 == SQUARE_SIZE) ? "\n" : "");
    std::cout << std::endl;
}

const size_t &Square::getId() const
{
    return _id;
}

void Square::addSquareLine(const std::string &line)
{
    size_t index = 0;

    for (; _square[index]; index++);
    for (size_t i = 0; i < line.size(); i++)
        _square[index + i] = line[i];
}

void Square::setSquare(const std::vector<char> &square)
{
    for (size_t y = 0; y < SQUARE_SIZE; y++)
        for (size_t x = 0; x < SQUARE_SIZE; x++)
            _square[x + (y * SQUARE_SIZE)] = square[x + (y * SQUARE_SIZE)];
}

const char &Square::operator[](size_t y) const
{
    return _square[y];
}

bool compareSquareRow(const Square s1, const Square s2)
{
    for (size_t x = 0; x < SQUARE_SIZE; x++)
        if (s1[x + (SQUARE_SIZE - 1) * SQUARE_SIZE] != s2[x])
            return false;
    return true;
}

bool compareSquareCol(const Square s1, const Square s2)
{
    for (size_t y = 0; y < SQUARE_SIZE; y++)
        if (s1[(SQUARE_SIZE - 1) + (y * SQUARE_SIZE)] != s2[y * SQUARE_SIZE])
            return false;
    return true;
}

void displayVector(const std::vector<Square> &v)
{
    size_t size = (size_t) std::sqrt((double) v.size());
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            std::cout << v[j + (i * size)].getId() << ((j + 1 == size) ? "\n" : ", ");
        }
    }
}

void displayV(const std::vector<Square> &v)
{
    std::cout << v.size() << std::endl;
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i].getId() << ((i + 1 == v.size()) ? "\n" : ", ");
}

bool createImage(std::vector<Square> image, const std::vector<Square> &imageParts, size_t imageSize)
{
    if (image.size() == imageParts.size()) {
        std::cout << "I got one" << std::endl;
        displayVector(image);
        return true;
    }

    for (size_t i = 0; i < imageParts.size(); i++) {
        Square square = imageParts[i];

        if (std::find_if(image.begin(), image.end(), [square](const Square &s) {
                return s.getId() == square.getId();
            }) != image.end())
            continue;

        for (size_t r = 0; r < 4; r++) {
            for (size_t fX = 0; fX < 2; fX++) {
                for (size_t fY = 0; fY < 2; fY++) {
                    size_t imageIndex = image.size();

                    if (imageIndex == 0) {
                        image.push_back(square);
                        if (createImage(image, imageParts, imageSize))
                            return true;
                        image.pop_back();
                    } else {
                        if (imageIndex < imageSize) {
                            Square prevSquare = image[imageIndex - 1];

                            if (compareSquareCol(prevSquare, square)) {
                                image.push_back(square);
                                if (createImage(image, imageParts, imageSize))
                                    return true;
                                image.pop_back();
                            }
                        } else if (imageIndex % imageSize == 0) {
                            Square prevSquare = image[imageIndex - imageSize];

                            if (compareSquareRow(prevSquare, square)) {
                                image.push_back(square);
                                if (createImage(image, imageParts, imageSize))
                                    return true;
                                image.pop_back();
                            }
                        } else {
                            Square prevSquareLeft = image[imageIndex - 1];
                            Square prevSquareUp = image[imageIndex - imageSize];

                            if (compareSquareCol(prevSquareLeft, square) && compareSquareRow(prevSquareUp, square)) {
                                image.push_back(square);
                                if (createImage(image, imageParts, imageSize))
                                    return true;
                                image.pop_back();
                            }
                        }
                    }
                    square.flipY();
                }
                square.flipX();
            }
            square.rotate();
        }
    }

    return false;
}

int main(void)
{
    std::string line;
    std::vector<Square> squares;

    while (std::getline(std::cin, line)) {
        if (line.substr(0, 4) == "Tile") {
            size_t id = std::stoul(line.substr(5, (line.size() - 1) - 5));

            squares.push_back(Square(id));
        } else if (!line.empty()) {
            squares[squares.size() - 1].addSquareLine(line);
        }
    }

    std::vector<Square> image;
    size_t imageSize = (size_t) std::sqrt((double) squares.size());
    std::cout << imageSize << std::endl;
    bool imageCreated = createImage(image, squares, imageSize);

    std::cout << ((imageCreated) ? "Created" : "Not created") << std::endl;

    return 0;
}
