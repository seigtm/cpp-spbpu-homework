// In an array of integers, determine the maximum count of consecutive identical elements.
// For built-in arrays, where the number and values of elements are
//  specified during initialization, create several arrays to test different cases.
// For an array allocated in dynamic memory, the number of elements should
//  be entered from the keyboard, and the values of the elements should be generated randomly.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>

/**
 * @brief Function to find the maximum count of consecutive equal elements in an array.
 *
 * @param arr An array of integers.
 * @param size The size of the array.
 * @return The maximum count of consecutive equal elements.
 */
int findMaxConsecutive(const int arr[], int size) {
    if(size <= 0)
        return 0;

    int maxConsecutive{ 1 };      // Initial value for the maximum consecutive element count.
    int currentConsecutive{ 1 };  // Initial value for the current consecutive element count.

    for(int i{ 1 }; i < size; ++i) {
        if(arr[i] == arr[i - 1])
            currentConsecutive++;
        else
            currentConsecutive = 1;
        maxConsecutive = std::max(maxConsecutive, currentConsecutive);
    }

    return maxConsecutive;
}

int main() {
    // Variant 1: Using built-in arrays:
    const int arr1[]{ 1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5 };
    const int size1{ sizeof(arr1) / sizeof(arr1[0]) };

    const int arr2[]{ 1, 1, 1, 1, 1, 2, 2, 3, 3, 4 };
    const int size2{ sizeof(arr2) / sizeof(arr2[0]) };

    std::cout << "Maximum count of consecutive equal elements in arr1: "
              << findMaxConsecutive(arr1, size1) << '\n';
    std::cout << "Maximum count of consecutive equal elements in arr2: "
              << findMaxConsecutive(arr2, size2) << '\n';

    // Variant 2: Using a dynamically allocated array:
    int size3;
    std::cout << "Enter the size of the array: ";
    std::cin >> size3;

    if(size3 <= 0) {
        std::cerr << "The size of the array must be a positive number.\n";
        return 1;
    }

    const auto arr3{ std::make_unique<int[]>(size3) };

    // Filling the array with random values:
    std::mt19937 generator{ std::random_device()() };
    // For simplicity, limiting values to [0;4].
    std::uniform_int_distribution distribution{ 0, 4 };
    for(int i{}; i < size3; ++i)
        arr3[i] = distribution(generator);

    std::cout << "Generated array: ";
    for(int i{}; i < size3; ++i)
        std::cout << arr3[i] << " ";

    std::cout << "\nMaximum count of consecutive equal elements in arr3: "
              << findMaxConsecutive(arr3.get(), size3) << '\n';
}
