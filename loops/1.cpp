// 1. Given the coordinates of a rook positioned on a chessboard square 
//    (row number and column number), write a loop (or loops) to 
//    output the coordinates of all squares under attack.
//    The rook can move any number of squares horizontally or vertically.

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

// Returns the coordinates of the cells that are under the attack of the rook.
std::vector<Coordinate> underAttack(const Coordinate& rook) {
    std::vector<Coordinate> attackedCells{};
    for(auto i{ 1 }; i <= PLAYBOARD_SIZE; ++i) {
        if(i != rook.col)
            attackedCells.emplace_back(Coordinate{ rook.row, i });
        if(i != rook.row)
            attackedCells.emplace_back(Coordinate{ i, rook.col });
    }
    return attackedCells;
}

int main() {
    Coordinate rook{};
    std::cout << "Enter the rook coordinates (row and column): ";
    std::cin >> rook;

    if(!Coordinate::isValidCoordinate(rook)) {
        std::cerr << "Incorrect input of the rook coordinates.\n"
                     "The value should be in the range [1; 8].\n";
        return -1;
    }

    for(const auto& cell : underAttack(rook))
        std::cout << "The cell " << cell << " could be attacked.\n";
}
