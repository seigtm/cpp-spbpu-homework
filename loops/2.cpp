// 2. Given the coordinates of a bishop positioned on a chessboard square
//    (row number and column number), write a loop (or loops) to output
//    the coordinates of all squares under attack. The bishop can move
//    any number of squares diagonally.

#include <cstdint>
#include <iostream>
#include <vector>

namespace {
constexpr uint8_t PLAYBOARD_SIZE{ 8 };
}  // Anonymous namespace.

struct Coordinate {
    int row{};
    int col{};

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& c) {
        return os << "(row = " << c.row << ", col = " << c.col << ")";
    }

    friend std::istream& operator>>(std::istream& is, Coordinate& c) {
        is >> c.row >> c.col;
        return is;
    }

    // Checks whether the coordinate is within the chessboard (8x8).
    static inline bool isValidCoordinate(const Coordinate& coord) {
        // clang-format off
        return coord.row >= 1 && coord.row <= PLAYBOARD_SIZE
            && coord.col >= 1 && coord.col <= PLAYBOARD_SIZE;
        // clang-format on
    }
};


// Returns the coordinates of the cells that are under the attack of the bishop.
std::vector<Coordinate> underAttack(const Coordinate& bishop) {
    std::vector<Coordinate> underAttackCoords{};
    Coordinate currentCoord{};
    // Let's loop through all possible directions of the bishop's movement on the chessboard.
    const Coordinate directions[4][2]{ { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 } };
    for(const auto& dir : directions) {
        for(auto i{ 1 }; i < PLAYBOARD_SIZE; ++i) {
            currentCoord = { bishop.row + i * dir->row, bishop.col + i * dir->col };
            if(Coordinate::isValidCoordinate(currentCoord))
                underAttackCoords.emplace_back(currentCoord);
            else  // Have reached the boundary of the board.
                break;
        }
    }
    return underAttackCoords;
}

int main() {
    Coordinate bishop{};
    std::cout << "Enter the bishop coordinates (row, column): ";
    std::cin >> bishop;

    if(!Coordinate::isValidCoordinate(bishop)) {
        std::cerr << "Incorrect input of the bishop coordinates.\n"
                     "The value should be in the range [1; 8].\n";
        return 1;
    }

    for(const auto& cell : underAttack(bishop))
        std::cout << "The cell " << cell << " could be attacked.\n";
}
