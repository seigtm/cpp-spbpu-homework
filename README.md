# C++ Homework Repository

Welcome to my C++ homework repository for the **"Programming Technologies"** course at **St. Petersburg Polytechnic University**.

## Overview

This repository serves as a collection of my assignments and projects related to the C++ programming language. Each folder in this repository corresponds to a specific homework assignment, containing the source code, documentation, and any relevant materials.

Feel free to explore the contents of each folder to gain insights into my learning journey and the projects I've worked on during the course.

## Course Information

- **Course**: Programming Technologies
- **Instructor**: Ilya Alexandrovich Shemyakin
- **Term**: Fall 2023

## Assignments overview

### Assignment 1: Chessboard Rook Attack Coordinates

- **Task**: Given the coordinates of a rook positioned on a chessboard square (row number and column number), write a loop (or loops) to output the coordinates of all squares under attack. The rook can move any number of squares horizontally or vertically.

- **Solution**: In the `loops/1.cpp` file, you can find the implementation of a program that takes the coordinates of a rook on an 8x8 chessboard and calculates and displays the coordinates of all squares under attack by the rook. The code includes a `Coordinate` struct for handling coordinates, a `Coordinate::isValidCoordinate` function for validation, and the `underAttack` function to calculate attacked squares.

### Assignment 2: Chessboard Bishop Attack Coordinates

- **Task**: Given the coordinates of a bishop positioned on a chessboard square (row number and column number), write a loop (or loops) to output the coordinates of all squares under attack. The bishop can move any number of squares diagonally.

- **Solution**: In the `loops/2.cpp` file, you can find the implementation of a program that takes the coordinates of a bishop on an 8x8 chessboard and calculates and displays the coordinates of all squares under attack by the bishop. The code includes a `Coordinate` struct for handling coordinates, a `Coordinate::isValidCoordinate` function for validation, and the `underAttack` function to calculate attacked squares.

### Assignment 3: Fibonacci Number Series

- **Task**: Write a program that displays a series of Fibonacci numbers on the screen, where each number is the sum of the two preceding ones (1, 2, 3, 5, 8, 13, 21, …).

- **Solution**: In the `loops/3.cpp` file, you can find the implementation of a program that generates and displays the Fibonacci number series. The program starts with the initial number 1 and then iteratively calculates and displays Fibonacci numbers until reaching a specified limit (1,000,000 in this case).

### Assignment 4: Sequence Analysis

- **Task**: Write a program that takes input of a sequence of integers, with the end of the sequence marked by the input of zero (zero is not considered a part of the sequence), and calculates the following statistics:
  1. The sum of all entered numbers.
  2. The arithmetic mean of all entered numbers.
  3. The arithmetic mean of entered positive numbers.
  4. The maximum value and its position among all entered numbers.
  5. The minimum positive value and its position among all entered numbers.

- **Solution**: In the `loops/4.cpp` file, you can find the implementation of a program that reads a sequence of integers from the user, performs the specified calculations, and displays the results. The program uses a loop with a precondition to handle input and calculate the statistics. It also considers special cases such as an empty sequence or the absence of positive numbers.

### Assignment 5: Exponent Calculation

- **Task**: Write a program that takes two numbers, 'a' and 'b,' from the keyboard and prints 'a' raised to the power of 'b'. The exponent 'b' should be an integer and can be negative.

- **Solution**: In the `loops/5.cpp` file, you can find the implementation of a program that reads two integers 'a' and 'b' from the user, calculates 'a' raised to the power of 'b' using the `std::pow` function from the C++ Standard Library, and displays the result. The program also handles potential errors such as incorrect input or overflow.

### Assignment 6: Roman Numeral Converter

- **Task**: Write a program that takes an integer (< 400) as input and prints its representation in Roman numerals.

- **Solution**: In the `loops/6.cpp` file, you can find the implementation of a program that reads an integer from the user and converts it to its Roman numeral representation. The program uses a list of Roman numeral symbols and their corresponding values to perform the conversion. It then displays the Roman numeral representation of the input integer.

### Assignment 7: Sum of Digits

- **Task**: Write a program that takes an integer and calculates the sum of its digits.

- **Solution**: In the `loops/7.cpp` file, you can find the implementation of a program that reads an integer from the user as a string and calculates the sum of its digits. The program validates whether the input is a valid integer (consisting of digits only) and then computes the sum of its digits using standard library functions.

### Assignment 8: Decimal Digit Presence Checker

- **Task**: Write a function that takes two parameters (integers) and returns true if the decimal digit specified by the first parameter is present in the decimal representation of the number specified by the second parameter. Leading zeros are not considered. Write a main function to test the task.

- **Solution**: In the `function/1.cpp` file, you can find the implementation of the function `bool setm::digitExists(uint8_t digit, int64_t number)` that checks for the presence of a specific digit in an integer. The `main` function is used to test this function with various test cases.

### Assignment 9: Prime Number Checker

- **Task**: Write a function to determine if a number is prime. A prime number is a number that is divisible only by 1 and itself (e.g., 2, 3, 5, 7, 11, 13, ...). Write a program that outputs all prime positive numbers less than the specified one.

- **Solution**: In the `functions/2.cpp` file, you can find the implementation of the function `constexpr bool setm::isPrime(unsigned number)` that efficiently checks if a given positive integer is a prime number. The `main` function uses this function to output all prime positive numbers between a specified lower and upper limit.

### Assignment 10: Numerical Integration and Runge's Rule

- **Task**: Write a function to compute the value of a definite integral using numerical integration methods like the trapezoidal rule. Determine accuracy using Runge's rule.

- **Solution**: In the `functions/3.cpp` file, you can find the implementation of numerical integration using the trapezoidal rule and Runge's rule. The code allows you to calculate the definite integral of a function within specified limits while ensuring a desired tolerance level.

  - The `trapezoidalIntegration` function computes the integral using the trapezoidal rule.
  - The `rungeRuleIntegration` function uses Runge's rule to determine the accuracy of the integral calculation.
  - The `integralFormula` function generates a string representing the integral formula.

- The example in `main` demonstrates the integration of the `sin(x)` function from `0` to `π` with a tolerance of `1e-12`.

### Assignment 11: Series Expansion and Error Handling

- **Task**: Write a function to calculate the value of the given sum at a specified point (x) with a specified absolute calculation error (absError) and a maximum number of terms (nMax). The sum represents the inverse square root of (1 + x) using a series expansion. Ensure that 'x' falls within the interval (-1, 1) and throw exceptions as needed for invalid input or insufficient accuracy.

- **Solution**: In the `functions/4.cpp` file, you can find the implementation of a function that calculates the inverse square root of (1 + x) using a series expansion. The code allows you to specify the input interval, step size, absolute error, and maximum number of terms. It then calculates and displays the results for both the custom implementation and the standard C++ `std::sqrt` function.

  - The `inverseSqrtOfOnePlusX` function computes the series expansion with error handling for valid input and accuracy requirements.

- The example in `main` demonstrates the calculation of the inverse square root for a range of 'x' values within a specified interval, controlling accuracy with error and term limits.

### Assignment 12: Binary Palindrome Checker

- **Task**: Write a function to determine whether a number is a palindrome in the binary number system (the binary representation of the number reads the same from left to right as it does from right to left).

- **Solution**: In the `functions/5.cpp` file, you can find two implementations of the binary palindrome checker:

  - `setm::v1::isBinaryPalindrome`: This version converts the integer to its binary representation as a string and checks if it's a palindrome. It's relatively simple and easy to understand but may not be the most efficient.

  - `setm::v2::isBinaryPalindrome`: This version directly operates on the binary representation of the integer, checking if it's a palindrome using bitwise operations. It's more memory and time efficient but may be less intuitive for some programmers.

Both implementations are provided to demonstrate different approaches to solving the same problem. The code also includes test cases to verify the correctness of both implementations.

### Assignment 13: Array Order Checker

- **Task**: Write a function called `isOrdered` that takes two parameters - the address of a one-dimensional array of integers and the number of elements, and returns true if the elements of the array are ordered in ascending order, and false otherwise.

- **Solution**: In the `arrays/1.cpp` file, you can find the implementation of the `isOrdered` function. The function checks if the given array is ordered in ascending order. It returns `true` if the elements of the array are in ascending order and `false` otherwise. The function handles cases of a null array pointer or a non-positive array size.

- The `main` function is used to demonstrate how to use the `isOrdered` function. It takes the size and elements of the array as input from the user and prints whether the array is ordered in ascending order.

### Assignment 14: Insertion Sort

- **Task**: Write the `insertionSort` function that sorts an array using the insertion sort method.

- **Solution**: In the `arrays/2.cpp` file, you can find the implementation of the `insertionSort` function, which sorts an array of integers in ascending order using the insertion sort algorithm. The function takes a pointer to the array and the number of elements as parameters. It iterates through the array, moving elements into their correct positions to achieve the sorted result.

- The `main` function demonstrates how to use the `insertionSort` function. It prompts the user to enter the size and elements of the array, sorts the array using insertion sort, and then displays the sorted array.

### Assignment 15: Closest Element Index in a Sorted Array

- **Task**: Write a recursive function `findValue` that determines the index of the element in a sorted array that is closest to the input number. The function returns the index of the first occurrence of the closest element.

- **Solution**: In the `arrays/3.cpp` file, you can find the implementation of the `findValue` function. This recursive function performs a binary search on a sorted array of integers, finding the index of the closest element to the input number. If there are multiple occurrences of the closest element, it returns the index of the first occurrence. The code also includes a set of tests in the `setm::test::Run` function to ensure the correctness of the implementation.

- The `main` function demonstrates how to use the `findValue` function. It prompts the user to enter the **size** and **elements of a sorted array**, as well as the **target number**. It then calls the `findValue` function and displays the closest element along with its index in the array.
