// 7. Write a program that takes an integer
//    and calculates the sum of its digits.

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <string>

int main() {
    std::cout << "Enter an integer: ";
    std::string input{};
    std::cin >> input;

    if(!std::all_of(input.begin(), input.end(), isdigit)) {
        std::cerr << "Error: Not an integer was entered." << std::endl;
        return 1;
    }

    const auto sum{ std::accumulate(input.begin(), input.end(), 0) - ('0' * input.length()) };
    std::cout << "The sum of the digits of the number: " << sum << std::endl;
}
