// 4. Write a program that takes input of a sequence of integers, with the end of the sequence
//    marked by the input of zero (zero is not considered a part of the sequence), and calculates:
//     1) the sum of all entered numbers;
//     2) the arithmetic mean of all entered numbers;
//     3) the arithmetic mean of entered positive numbers;
//     4) the maximum value and its position among all entered numbers;
//     5) the minimum positive value and its position among all entered numbers.
//    Notes:
//     1) You cannot use arrays;
//     2) Use only a loop with a precondition to solve this problem.

#include <iostream>
#include <limits>

int main() {
    auto sum{ 0 };
    auto maxValue{ std::numeric_limits<int>::min() };
    auto maxValuePosition{ -1 };
    auto minPositiveValue{ std::numeric_limits<int>::max() };
    auto minPositiveValuePosition{ -1 };
    auto count{ 0 };
    auto countPositive{ 0 };
    auto sumPositive{ 0 };

    std::cout << "Enter a sequence of integers (enter 0 to end):\n";
    for(auto num{ 0 }; std::cin >> num && num; ++count, sum += num) {
        if(num > maxValue) {
            maxValue = num;
            maxValuePosition = count + 1;
        }
        if(num > 0) {
            countPositive++;
            sumPositive += num;
            if(num < minPositiveValue) {
                minPositiveValue = num;
                minPositiveValuePosition = count + 1;
            }
        }
    }

    if(std::cin.fail()) {
        std::cerr << "Not a number was detected. Incorrect input.\n";
        return -1;
    }

    if(count == 0) {
        std::cout << "The sequence is empty.\n";
        return 0;
    }

    std::cout << "Sum of all numbers: " << sum << ".\n"
              << "Average of all numbers: " << static_cast<double>(sum) / count << ".\n"
              << "Maximum value: " << maxValue << " (position " << maxValuePosition << ").\n";

    // If there were no positive numbers in the sequence.
    if(minPositiveValuePosition == -1) {
        std::cout << "Only negative numbers were entered.\n";
        return 0;
    }

    std::cout << "Average of positive numbers: " << static_cast<double>(sumPositive) / countPositive << ".\n"
              << "Minimum positive value: " << minPositiveValue << " (position " << minPositiveValuePosition << ").\n";
}
