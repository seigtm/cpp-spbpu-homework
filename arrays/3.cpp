// 3. Write a recursive function findValue that finds the value
//    of an element in a sorted array that is closest to the
//    input number. Try to write a function that returns the
//    index of this element (if there are multiple occurrences,
//    return the index of the first one).

#include <cassert>
#include <iostream>
#include <memory>
#include <cmath>
#include <limits>

namespace setm {

/**
 * Performs a binary search on a sorted integer array.
 *
 * @param arr The pointer to the sorted integer array.
 * @param low The lower index of the search range.
 * @param high The upper index of the search range.
 * @param target The value to search for in the array.
 *
 * @return The index of the target value in the array,
 *         or -1 if `arr` is nullptr.
 */
int binarySearch(const int* arr, int left, int right, int target) {
    // Handle null pointer case or out of bounds.
    if(!arr || left > right)
        return -1;
    // Base case: when there is only one element in the array.
    if(left == right)
        return left;

    int mid{ (left + right) / 2 };
    left = binarySearch(arr, left, mid, target);
    right = binarySearch(arr, mid + 1, right, target);

    // Return the index of the first element closest to the target.
    return std::abs(arr[left] - target) <= std::abs(arr[right] - target)
               ? left
               : right;
}

/**
 * Checks if an array is sorted in ascending order.
 *
 * @param arr a pointer to the array to be checked.
 * @param size the size of the array.
 *
 * @return true if the array is sorted, false otherwise.
 */
bool isSorted(const int* arr, int size) {
    for(int i{ 1 }; i < size; ++i)
        if(arr[i] < arr[i - 1])
            return false;

    return true;
}

namespace test {

void Run() {
    // Test 1: Valid input with a sorted array.
    const int arr1[]{ 2, 4, 6, 8, 10 };
    int size1{ sizeof(arr1) / sizeof(arr1[0]) };
    int target1{ 6 };
    int result1{ binarySearch(arr1, 0, size1 - 1, target1) };
    assert(result1 == 2);

    // Test 2: Valid input with an empty (nullptr) array.
    const int* arr2{ nullptr };
    int size2{};
    int target2{ 7 };
    int result2{ binarySearch(arr2, 0, size2 - 1, target2) };
    assert(result2 == -1);

    // Test 3: Valid input with a single-element array.
    const int arr3[]{ 3 };
    int size3{ 1 };
    int target3{ 3 };
    int result3{ binarySearch(arr3, 0, size3 - 1, target3) };
    assert(result3 == 0);

    // Test 4: Valid input with a single-element array and a different target.
    const int target4{ 5 };
    int result4{ binarySearch(arr3, 0, size3 - 1, target4) };
    assert(result4 == 0);

    // Test 5: Valid input with a single-element array and a different target.
    const int arr5[]{ 8 };
    int size5{ 1 };
    int target5{ 10 };
    int result5{ binarySearch(arr5, 0, size5 - 1, target5) };
    assert(result5 == 0);

    // Test 6: Valid input with a non-existent target.
    const int arr6[]{ 1, 3, 7, 9 };
    int size6{ sizeof(arr6) / sizeof(arr6[0]) };
    int target6{ 6 };
    int result6{ binarySearch(arr6, 0, size6 - 1, target6) };
    assert(result6 == 2);

    // Test 7: Invalid input with a null pointer.
    const int* arr7{ nullptr };
    int size7{ 5 };
    int target7{ 6 };
    int result7{ binarySearch(arr7, 0, size7 - 1, target7) };
    assert(result7 == -1);

    // Test 8: Invalid input with an empty array.
    const int arr8[]{};
    int size8{ 0 };
    int target8{ 6 };
    int result8{ binarySearch(arr8, 0, size8 - 1, target8) };
    assert(result8 == -1);

    // Test 9: Valid input with multiple elements and multiple targets.
    const int arr9[]{ 0, 7, 7, 7, 7 };
    int size9{ sizeof(arr9) / sizeof(arr9[0]) };
    int target9{ 7 };
    int result9{ binarySearch(arr9, 0, size9 - 1, target9) };
    assert(result9 == 1);
}

}  // namespace test

}  // namespace setm

int main() {
    int size{};

    std::cout << "Enter the size of the sorted array: ";
    while(!(std::cin >> size) || size <= 0) {
        std::cout << "Invalid input. Please enter a valid size: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    auto arrPtr{ std::make_unique<int[]>(size) };

    std::cout << "Enter the elements of the sorted array:\n";
    for(int i{}; i < size; ++i) {
        while(!(std::cin >> arrPtr[i])) {
            std::cout << "Invalid input. Please enter a valid element: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if(!setm::isSorted(arrPtr.get(), size)) {
        std::cerr << "The input array is not sorted in ascending order.\n";
        return 1;
    }

    int target;
    std::cout << "Enter the target number: ";
    while(!(std::cin >> target)) {
        std::cout << "Invalid input. Please enter a valid target number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(int index{ setm::binarySearch(arrPtr.get(), 0, size - 1, target) }; index != -1)
        std::cout << "The element closest to " << target << " is " << arrPtr[index]
                  << " at index " << index << '\n';
    else
        std::cout << "No element found." << '\n';

    std::cout << "Now we would perform a set of tests.\n";
    setm::test::Run();
    std::cout << "All test cases passed.\n";
}
