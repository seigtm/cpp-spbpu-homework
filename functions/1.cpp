// 1. Write a function that takes two parameters (integers)
//    and returns true if the decimal digit specified by
//    the first parameter is present in the decimal
//    representation of the number specified by the
//    second parameter. Leading zeros are not considered.
//    Write a main function to test the task.

#include <cstdint>
#include <cmath>
#include <iostream>

namespace setm {

bool digitExists(uint8_t digit, int64_t number) {
    number = std::abs(number);
    while((number > 0) && (number % 10 != digit))
        number /= 10;
    return (number != 0) && (number % 10 == digit);
}

}  // namespace setm


int main() {
    const auto test{ [](uint8_t digit, int64_t number) {
        // Check and output the result.
        if(setm::digitExists(digit, number))
            std::cout << "The digit " << +digit << " is present in the number " << number << "\n";
        else
            std::cout << "The digit " << +digit << " is not present in the number " << number << "\n";
    } };

    test(1, 12345);
    test(3, 12345);
    test(5, 12345);
    test(0, 12345);
    test(0, 10345);
    test(9, 12345);
    test(12, 12345);
    test(1, -12345);
}
