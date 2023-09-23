// 6. Write a program that takes an integer (< 400) as input
//    and prints its representation in Roman numerals.

#include <iostream>
#include <initializer_list>
#include <utility>

std::string intToRoman(int num) {
    const auto romanSymbols = {
        std::make_pair(100, "C"),
        std::make_pair(90, "XC"),
        std::make_pair(50, "L"),
        std::make_pair(40, "XL"),
        std::make_pair(10, "X"),
        std::make_pair(9, "IX"),
        std::make_pair(5, "V"),
        std::make_pair(4, "IV"),
        std::make_pair(1, "I")
    };

    std::string result{};
    for(const auto& [arabic, roman] : romanSymbols) {
        while(num >= arabic) {
            result.append(roman);
            num -= arabic;
        }
    }

    return result;
}

int main() {
    std::cout << "Enter an integer (0 < int < 400): ";
    int num{};
    if(!(std::cin >> num) || 0 >= num || num >= 400) {
        std::cerr << "Error: Incorrect input.\nPlease enter an integer between 1 and 399.\n";
        return 1;
    }

    std::cout << "Roman numeral: " << intToRoman(num) << "\n";
}
