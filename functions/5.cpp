// 5. Write a function to determine whether a number is a palindrome
//    in the binary number system (the binary representation of the
//    number reads the same from left to right as it does from right to left).

#include <algorithm>
#include <bitset>
#include <cassert>
#include <concepts>
#include <climits>
#include <iostream>
#include <iterator>
#include <string>

namespace setm {

namespace v1 {

/**
 * @brief Checks if the binary representation of an integer is a palindrome.
 *
 * @param number The input integer.
 * @return True if the binary representation is a palindrome, false otherwise.
 *
 * @note Pros:
 *       - Simplicity: The code is relatively straightforward and easy to understand.
 *       - Reusability: It can be used with various integer types thanks to the use of templates (std::integral auto).
 *       - Conceptual clarity: The code explicitly converts the number to a binary string and checks for palindromic behavior.
 *
 * @note Cons:
 *       - Efficiency: It may not be the most efficient approach due to the conversion to a binary string and string manipulation.
 *       - Extra memory usage: Converting to a binary string involves creating an additional string variable.
 */
bool isBinaryPalindrome(std::integral auto number) {
    // Convert the integer to a binary string.
    auto binary_representation{ std::bitset<sizeof(number) * CHAR_BIT>(number).to_string() };
    // Remove leading zeroes.
    binary_representation.erase(0, binary_representation.find('1'));
    // Create a reversed binary representation.
    const std::string binary_representation_reverse{ binary_representation.rbegin(), binary_representation.rend() };

    // Check if the binary representation is a palindrome.
    return binary_representation == binary_representation_reverse;
}

}  // namespace v1

namespace v2 {

/**
 * @brief Checks if the binary representation of an integer is a palindrome.
 *
 * @param number The input integer.
 * @return True if the binary representation is a palindrome, false otherwise.
 *
 * @note Pros:
 *       - Efficiency: This approach operates directly on the binary representation without any intermediate string conversion, making it more memory and time efficient.
 *       - No additional memory usage: It doesn't create additional string variables.
 *
 * @note Cons:
 *       - Complexity: The code uses bitwise operations, which might be less intuitive for some programmers.
 */
bool isBinaryPalindrome(unsigned int number) {
    // The reverse of the binary representation of the number.
    unsigned int number_reverse{};
    // Process all bits of the input number.
    unsigned int k{ number };
    while(k != 0) {
        // Add the rightmost bit to `number_reverse`.
        number_reverse = (number_reverse << 1) | (k & 1);
        // Drop the last bit.
        k = k >> 1;
    }

    // Check if the input number is equal to its binary reverse.
    return number == number_reverse;
}

}  // namespace v2

}  // namespace setm

int main() {
    const auto test_cases = {
        // Positive palindromes.
        std::make_pair(1, true),
        std::make_pair(3, true),
        std::make_pair(5, true),
        std::make_pair(7, true),
        std::make_pair(9, true),
        std::make_pair(15, true),
        std::make_pair(17, true),
        std::make_pair(21, true),
        std::make_pair(27, true),
        std::make_pair(31, true),
        // Negative palindromes.
        std::make_pair(-1, true),
        std::make_pair(-98305, true),
        std::make_pair(-147457, true),
        std::make_pair(-245761, true),
        std::make_pair(-270337, true),
        std::make_pair(-368641, true),
        std::make_pair(-417793, true),
        std::make_pair(-516097, true),
        std::make_pair(-528385, true),
        std::make_pair(-626689, true),

        // Positive NOT palindromes.
        std::make_pair(2, false),
        std::make_pair(4, false),
        std::make_pair(6, false),
        std::make_pair(8, false),
        std::make_pair(12, false),
        std::make_pair(16, false),
        std::make_pair(20, false),
        std::make_pair(25, false),
        std::make_pair(30, false),
        std::make_pair(69, false),
        // Negative NOT palindromes.
        std::make_pair(-2, false),
        std::make_pair(-300, false),
        std::make_pair(-400, false),
        std::make_pair(-250000, false),
        std::make_pair(-270336, false),
        std::make_pair(-37000, false),
        std::make_pair(-417792, false),
        std::make_pair(-516093, false),
        std::make_pair(-528386, false),
        std::make_pair(-626691, false),
    };

    for(const auto [number, expectation] : test_cases) {
        assert(setm::v1::isBinaryPalindrome(number) == expectation);
        assert(setm::v2::isBinaryPalindrome(number) == expectation);
    }

    std::cout << "All test cases passed with success!\n";
}
