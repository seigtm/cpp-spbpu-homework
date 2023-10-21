// 2. Write the insertionSort function that
//    sorts an array using the insertion method

#include <iostream>
#include <memory>

/**
 * Sorts an array in ascending order using the insertion sort algorithm.
 *
 * @param arr a pointer to the array to be sorted
 * @param n the number of elements in the array
 */
void insertionSort(int* arr, int n) {
    for(int i{1}; i < n; ++i) {
        int key{ arr[i] };
        int j{ i - 1 };

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position.
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

int main() {
    std::cout << "Enter the size of the array: ";
    int size{};
    if(!(std::cin >> size) || size <= 0) {
        std::cerr << "Error: The size of the array must be positive.\n";
        return -1;
    }

    std::cout << "Enter " << size << " elements of the array: ";
    auto arr{ std::make_unique<int[]>(size) };
    for(int i{}; i < size; ++i) {
        if(!(std::cin >> arr[i])) {
            std::cerr << "Error: Input must be integers.\n";
            return -1;
        }
    }

    insertionSort(arr.get(), size);

    std::cout << "The sorted array is: ";
    for(int i{}; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
