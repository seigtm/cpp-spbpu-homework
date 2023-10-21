// 4. Write a function isVarName that takes one parameter (a character string)
//    and checks the correctness of a variable name in C++. The name may only
//    contain Latin letters (both uppercase and lowercase), digits, and
//    underscores, but it cannot start with a digit. The function should return
//    true if the name is written correctly, and false otherwise.
//    You can use library functions from the <cctype> header.

#include <cassert>
#include <cctype>
#include <iostream>
#include <string_view>

namespace setm {

/**
 * @brief Check the correctness of a C++ variable name.
 *
 * This function verifies whether a given string conforms to the rules for a valid
 * C++ variable name. A valid variable name may only contain Latin letters (both
 * uppercase and lowercase), digits, and underscores, but it cannot start with a digit.
 *
 * @param name The string to be checked as a potential C++ variable name.
 * @return True if the name is a valid C++ variable name, false otherwise.
 *
 * @note The function does not consider any reserved words.
 */
bool isVarName(std::string_view name) {
    if(name.empty() || std::isdigit(name.front()))
        return false;

    for(char c : name)
        if(!std::isalnum(c) && c != '_')
            return false;

    return true;
}

namespace test {

void Run() {
    // Valid variable names:
    assert(isVarName("myVar"));       // Alphanumeric with lowercase letters.
    assert(isVarName("AnotherVar"));  // Alphanumeric with uppercase letters.
    assert(isVarName("var_123"));     // Alphanumeric with underscores.
    assert(isVarName("_var"));        // Starts with an underscore.

    // Invalid variable names:
    assert(!isVarName("123var"));  // Starts with a digit.
    assert(!isVarName("my-Var"));  // Contains invalid character '-'.
    assert(!isVarName("my Var"));  // Contains space.
    assert(!isVarName(""));        // Empty string.
}

}  // namespace test

}  // namespace setm

int main() {
    std::string variableName;
    std::cout << "Enter a variable name: ";
    // Use getline to handle spaces.
    std::getline(std::cin, variableName);

    if(setm::isVarName(variableName))
        std::cout << "Valid variable name.\n";
    else
        std::cout << "Invalid variable name.\n";

    std::cout << "Now we would perform a set of tests.\n";
    setm::test::Run();
    std::cout << "All test cases passed.\n";
}
