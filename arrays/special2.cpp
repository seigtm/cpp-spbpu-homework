// Create a new string from characters that are repeated more
//  than once in the original string (they should appear only
//  once in the new string).

#include <cstdlib>        // EXIT_FAILURE.
#include <fstream>        // File I/O.
#include <iostream>       // Input/Output operations.
#include <string>         // String class.
#include <stdexcept>      // Exceptions.
#include <unordered_map>  // HashMap.

namespace setm {

/**
 * @brief Find repetitive characters in a string.
 *
 * This function takes a string as input and returns a new string
 * containing characters that appear more than once in the input string.
 *
 * @param source The input string to analyze.
 * @return A string containing the repetitive characters.
 */
std::string repetitiveCharsInStr(const std::string& source) {
    // Count character occurrences.
    std::unordered_map<char, int> chars{};
    for(char c : source)
        chars[c]++;

    // Append repetitive characters to the result string.
    std::string result{};
    for(const auto& [key, value] : chars)
        if(value > 1)
            result += key;

    return result;
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
 * @return A pointer to the null-terminated destination string.
 */
char* repetitiveCharsInStr(char* destination, const char* source) {
    if(destination == nullptr || source == nullptr)
        return nullptr;

    // Count character occurrences.
    std::unordered_map<char, int> chars;

    // Iterate through the source string.
    while(*source) {
        chars[*source]++;
        source++;
    }

    char* dest = destination;
    for(const auto& [key, value] : chars) {
        if(value > 1) {
            *dest++ = key;
        }
    }

    // Null-terminate the destination string.
    *dest = '\0';

    return destination;
}

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
            const std::string result{ setm::repetitiveCharsInStr(sourceStr) };
            std::cout << "Original: " << sourceStr
                      << "\nRepetitive: " << result << '\n';

            // Using the C-style character array version:
            dest = new char[length + 1];  // Allocate memory for dest.
            const char* repetitiveChars{ setm::repetitiveCharsInStr(dest, source) };
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
