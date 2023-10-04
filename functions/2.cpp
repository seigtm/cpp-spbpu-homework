// 2. Write a function to determine if a number is prime. A prime number
//    is a number that is divisible only(!) by 1 and itself (2, 3, 5, 7, 11, 13, ...).
//    Write a program that outputs all prime positive numbers less than the specified one.

#include <cmath>
#include <iostream>

namespace setm {

/**
 * @brief Check if a given positive integer is a prime number.
 *
 * A prime number is a positive integer greater than 1 that has no positive divisors
 * other than 1 and itself.
 *
 * @param n The positive integer to be checked for primality.
 * @return true if the input is a prime number, false otherwise.
 *
 * @note This function efficiently checks if the given number is prime by
 *       using optimized algorithms to minimize the number of divisions.
 *       Time complexity ≈ O(sqrt(number)).
 *       Space complexity = O(1).
 *
 * @see https://en.wikipedia.org/wiki/Prime_number
 */
bool isPrime(unsigned long number) {
    if(number <= 1)
        return false;
    if(number <= 3)
        return true;
    if(number % 2 == 0)
        return false;

    for(auto divisor{ 3UL }; divisor * divisor <= number; divisor += 2)
        if(number % divisor == 0)
            return false;

    return true;
}

}  // namespace setm

int main() {
    constexpr auto lower_limit{ 2UL };
    constexpr auto upper_limit{ 98UL };
    for(auto number{ lower_limit }; number < upper_limit; ++number)
        if(setm::isPrime(number))
            std::cout << number << " ";
    std::cout << "\n";
}
