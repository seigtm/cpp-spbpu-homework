// 3. Write a program that displays a series of Fibonacci numbers on the screen,
//    where each number is the sum of the two preceding ones (1, 2, 3, 5, 8, 13, 21, …).

#include <cstdint>
#include <iostream>

namespace {

constexpr uint64_t FIB_END{ 1'000'000 };

}  // Anonymous namespace.

int main() {
    uint64_t num1{ 1 };
    uint64_t num2{ 1 };
    std::cout << num1 << " ";

    while(num2 <= FIB_END) {
        std::cout << num2 << " ";
        num2 += num1;
        num1 = num2 - num1;
    }

    std::cout << "\n";
}
