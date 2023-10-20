// 1. Write a function called isOrdered that takes two parameters - the address
//    of a one-dimensional array of integers and the number of elements,
//    and returns true if the elements of the array are ordered in
//    ascending order, and false otherwise.

#include <iostream>
#include <memory>

/**
 * Checks if the given array is ordered in ascending order.
 *
 * @param arr a pointer to the array
 * @param size the size of the array
 *
 * @return true if the array is ordered, false otherwise
 */
bool isOrdered(const int* arr, int size) {
    if(arr == nullptr || size <= 0)
        return false;

    for(int i{}; i < size - 1; ++i)
        if(arr[i] > arr[i + 1])
            return false;

    return true;
}

int main() {
    int size{};
    std::cout << "Enter the size of the array: ";
    if(!(std::cin >> size) || size <= 0) {
        std::cerr << "Error: The size of the array must be positive.\n";
        return -1;
    }

    auto arr{ std::make_unique<int[]>(size) };
    std::cout << "Enter " << size << " elements of the array: ";
    for(int i{}; i < size; ++i) {
        if(!(std::cin >> arr[i])) {
            std::cerr << "Error: Input must be integers.\n";
            return -1;
        }
    }

    std::cout << (isOrdered(arr.get(), size)
                      ? "The array is ordered\n"
                      : "The array is not ordered\n");
}
