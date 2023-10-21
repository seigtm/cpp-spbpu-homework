// 5. Write a function called removeChar that forms a new string by removing a specified character
//    from the original one. The pointer to the new string should be passed as a parameter.

#include <iostream>
#include <cstring>
#include <memory>

namespace setm {

/**
 * @brief Remove a specified character from a C-style string.
 *
 * This function removes all occurrences of a specified character from the input C-style string
 * and stores the result in the output C-style string. The memory for the output string should
 * be allocated by the caller and must have enough space to hold the modified string.
 *
 * @param inputString The input C-style string from which the character is to be removed.
 * @param charToRemove The character to be removed from the input string.
 * @param outputString The C-style string where the modified result will be stored.
 *
 * @note The function assumes that the memory for the output string has been allocated by the caller
 * and that it can accommodate the modified string. It also assumes that the input string is null-terminated.
 * Ensure proper memory management, including releasing memory for the output string when no longer needed.
 */
void removeChar(const char* inputString, char charToRemove, char* outputString) {
    int outputIndex{ 0 };

    for(int i = 0; inputString[i] != '\0'; ++i) {
        if(inputString[i] != charToRemove) {
            outputString[outputIndex] = inputString[i];
            outputIndex++;
        }
    }

    outputString[outputIndex] = '\0';
}

}  // namespace setm

int main() {
    const char* inputString{ "Hello, World!" };
    const char charToRemove{ 'o' };

    auto newSize{ std::strlen(inputString) + 1 };  // +1 for '\0'.
    auto outputString(std::make_unique<char[]>(newSize));

    setm::removeChar(inputString, charToRemove, outputString.get());

    std::cout << "Original: " << inputString
              << "\nAfter removing '" << charToRemove << "': " << outputString << '\n';
}
