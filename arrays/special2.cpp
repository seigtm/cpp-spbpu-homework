// Create a new string from characters that are repeated more
//  than once in the original string (they should appear only
//  once in the new string).

#include <cstdlib>        // EXIT_FAILURE.
#include <cstring>        // v2 uses std::strchr().
#include <fstream>        // File I/O.
#include <iostream>       // Input/Output operations.
#include <string>         // String class.
#include <stdexcept>      // Exceptions.
#include <unordered_map>  // HashMap.

namespace setm {

namespace v1 {

/**
 * @brief Find repetitive characters in a string.
 *
 * This function takes a string as input and returns a new string
 * containing characters that appear more than once in the input string.
 *
 * @param source The input string to analyze.
 * @return A string containing the repetitive characters, or an empty string if none are found.
 */
std::string repetitiveCharsInStr(const std::string& source) {
    // Count character occurrences.
    std::unordered_map<char, int> charCounts{};
    for(char currentChar : source)
        charCounts[currentChar]++;

    // Append repetitive characters to the result string.
    std::string repetitiveCharacters;
    for(const auto& [currentChar, count] : charCounts)
        if(count > 1)
            repetitiveCharacters += currentChar;

    return repetitiveCharacters;
}

/**
 * @brief Find repetitive characters in a C-style character array.
 *
 * This function takes a C-style character array as input and modifies another
 * character array to contain characters that appear more than once in the
 * input string (they should appear only once in the new string).
 *
 * @param destination A character array to store the repetitive characters.
 * @param source A C-style character array to analyze.
 * @return A pointer to the null-terminated destination string, or nullptr if there are no repetitive characters.
 */
char* repetitiveCharsInStr(char* destination, const char* source) {
    if(destination == nullptr || source == nullptr)
        return nullptr;

    // Count character occurrences.
    std::unordered_map<char, int> charCounts;

    // Iterate through the source string.
    while(*source) {
        charCounts[*source]++;
        source++;
    }

    char* dest{ destination };
    for(const auto& [currentChar, count] : charCounts) {
        if(count > 1) {
            *dest++ = currentChar;
        }
    }

    // Null-terminate the destination string.
    *dest = '\0';

    return destination;
}

}  // namespace v1

namespace v2 {

/**
 * @brief Find repetitive characters in a string.
 *
 * This function takes a string as input and returns a new string
 * containing characters that appear more than once in the input string.
 *
 * @param source The input string to analyze.
 * @return A string containing the repetitive characters, or an empty string if none are found.
 */
std::string repetitiveCharsInStr(const std::string& source) {
    std::string repetitiveCharacters;
    for(size_t i{}; i < source.length(); ++i) {
        const char currentChar{ source[i] };
        bool foundDuplicate{ false };

        // Check if the character appears before the current position.
        for(size_t j{}; j < i; ++j) {
            if(source[j] == currentChar) {
                foundDuplicate = true;
                break;
            }
        }

        // Append the character to the repetitiveCharacters if it's a duplicate.
        if(foundDuplicate && repetitiveCharacters.find(currentChar) == std::string::npos) {
            repetitiveCharacters += currentChar;
        }
    }

    return repetitiveCharacters;
}

/**
 * @brief Find repetitive characters in a C-style character array.
 *
 * This function takes a C-style character array as input and modifies another
 * character array to contain characters that appear more than once in the
 * input string (they should appear only once in the new string).
 *
 * @param destination A character array to store the repetitive characters.
 * @param source A C-style character array to analyze.
 * @return A pointer to the null-terminated destination string, or nullptr if there are no repetitive characters.
 */
char* repetitiveCharsInStr(char* destination, const char* source) {
    if(destination == nullptr || source == nullptr)
        return nullptr;

    size_t destIndex{};
    for(size_t i{}; source[i] != '\0'; ++i) {
        char currentChar{ source[i] };
        bool foundDuplicate{ false };

        // Check if the character appears before the current position.
        for(size_t j{}; j < i; ++j) {
            if(source[j] == currentChar) {
                foundDuplicate = true;
                break;
            }
        }

        // Append the character to the destination if it's a duplicate.
        if(foundDuplicate && std::strchr(destination, currentChar) == nullptr) {
            destination[destIndex++] = currentChar;
        }
    }

    // Null-terminate the destination string.
    destination[destIndex] = '\0';

    return destination;
}

}  // namespace v2

namespace v3 {

// The constant representing the full length of the extended ASCII character set,
// which contains 256 characters, including standard ASCII characters and additional
// extended characters with codes beyond the standard 7-bit ASCII range.
static constexpr auto ASCII_CHARACTERS_COUNT{ 256 };

/**
 * @brief Find repetitive characters in a string.
 *
 * This function takes a string as input and returns a new string
 * containing characters that appear more than once in the input string.
 *
 * @param source The input string to analyze.
 * @return A string containing the repetitive characters, or an empty string if none are found.
 */
std::string repetitiveCharsInStr(const std::string& source) {
    // Count character occurrences using a plain array.
    unsigned char charCounts[ASCII_CHARACTERS_COUNT] = { 0 };
    // Append repetitive characters to the result string.
    std::string repetitiveCharacters;

    for(unsigned char currentChar : source) {
        charCounts[currentChar]++;
        if(charCounts[currentChar] == 2)
            repetitiveCharacters += currentChar;
    }

    return repetitiveCharacters;
}

/**
 * @brief Find repetitive characters in a C-style character array.
 *
 * This function takes a C-style character array as input and modifies another
 * character array to contain characters that appear more than once in the
 * input string (they should appear only once in the new string).
 *
 * @param destination A character array to store the repetitive characters.
 * @param source A C-style character array to analyze.
 * @return A pointer to the null-terminated destination string, or nullptr if there are no repetitive characters.
 */
char* repetitiveCharsInStr(char* destination, const char* source) {
    if(destination == nullptr || source == nullptr)
        return nullptr;

    // Count character occurrences using a plain array.
    unsigned char charCounts[ASCII_CHARACTERS_COUNT] = { 0 };
    char* dest{ destination };

    // Iterate through the source string.
    while(*source) {
        const auto currentChar{ static_cast<unsigned char>(*source) };
        charCounts[currentChar]++;
        if(charCounts[currentChar] == 2)
            *dest++ = currentChar;
        source++;
    }

    // Null-terminate the destination string.
    *dest = '\0';

    return destination;
}

}  // namespace v3

}  // namespace setm

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>\n";
        std::exit(EXIT_FAILURE);
    }

    const char* inputFilePath{ argv[1] };
    std::ifstream inputFile{ inputFilePath };
    if(!inputFile.is_open()) {
        std::cerr << "Failed to open the input file: " << inputFilePath << '\n';
        std::exit(EXIT_FAILURE);
    }

    // Read the length of the string.
    unsigned int length{};
    while(inputFile >> length) {
        char* source{ nullptr };
        char* dest{ nullptr };

        try {
            inputFile.ignore();                     // Skip the newline character after the number.
            source = new char[length + 1];          // Allocate memory for source.
            inputFile.getline(source, length + 1);  // Read the string characters.

            // Using the C++ string version:
            const std::string sourceStr{ source };
            const std::string result{ setm::v3::repetitiveCharsInStr(sourceStr) };
            std::cout << "Original: " << sourceStr
                      << "\nRepetitive: " << result << '\n';

            // Using the C-style character array version:
            dest = new char[length + 1];  // Allocate memory for dest.
            const char* repetitiveChars{ setm::v3::repetitiveCharsInStr(dest, source) };
            std::cout << "Original (C-style): " << source
                      << "\nRepetitive (C-style): " << repetitiveChars << "\n\n";
        } catch(const std::bad_alloc& exception) {
            std::cerr << "Memory allocation failed; skipping this entry.\n"
                      << exception.what() << '\n';
        } catch(const std::invalid_argument& exception) {
            std::cerr << "String to integer conversion failed; no conversion could be performed.\n"
                      << exception.what() << '\n';
        } catch(const std::out_of_range& exception) {
            std::cerr << "String to integer conversion failed; no conversion could be performed.\n"
                      << exception.what() << '\n';
        } catch(const std::exception& exception) {
            std::cerr << "Unexpected exception: " << typeid(exception).name() << '\n'
                      << exception.what() << '\n';
        }

        delete[] source;
        delete[] dest;
    }

    inputFile.close();
}
