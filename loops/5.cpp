// 5. Write a program that takes two numbers, 'a' and 'b,' from the keyboard
//    and prints 'a' raised to the power of 'b'. The exponent 'b' should be
//    an integer and can be negative.

#include <cmath>
#include <iostream>

int main() {
    std::cout << "Enter two integers, a and b to calculate a^b: ";
    auto a{ 0 }, b{ 0 };
    if(!(std::cin >> a >> b)) {
        std::cerr << "Error: Incorrect input.\nPlease enter two integers.\n";
        return 1;
    }

    // NOTE: I'm ignoring the 0^0 case here 
    //       and using a standard STL pow that says <0^0 == 1>.
    // ¯\_( ͡° ͜ʖ ͡°)_/¯
    const auto result{ std::pow(a, b) };
    if(std::isnan(result) || std::isinf(result)) {
        std::cerr << "Error: Overflow or NaN.\n";
        return 1;
    }

    std::cout << a << "^" << b << " = " << result << "\n";
}
