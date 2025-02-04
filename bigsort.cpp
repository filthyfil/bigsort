/*
    BIG SORT - SORT IN CONSTANT TIME! 
    ==================================
    ASSUMPTIONS:
    - No duplicate values in the input array.
    - Input contains only positive integers.

    PROGRAM FLOW:
     > create an array (vector) `int arr[]`
     > create sparse presence array (vector) `bool exists[]`, true indicates presence, its index indicates value
     > iterate over exists[] and if true, push the index i into the array (vector) `int sorted`

    PERFORMANCE:
    - Time Complexity: O(n + k) (linear, where `k = maxElement`).
    - Space Complexity: O(k) (memory usage scales with the largest element).
*/

#include <iostream>
#include <vector>
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time()
#include <algorithm>  // For std::max_element
#include <chrono>     // For high-resolution timer

// Function to generate a random array of given size with positive integers
void generateRandomArray(std::vector<int>& arr, int minValue = 1, int maxValue = 100) {
    for (int& value : arr) {
        value = minValue + (std::rand() % (maxValue - minValue + 1));
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random number generator

    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    // Create and fill the original array
    std::vector<int> arr(size);
    std::cout << "Enter max element size: ";
    unsigned int max;
    std::cin >> max;
    generateRandomArray(arr, 1, max); // Using a small range for better visualization

    // Print the original array
    std::cout << "Original Array: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Start the timer (timing the sorting process)
    auto startTime = std::chrono::high_resolution_clock::now();

    // Find the maximum element in the original array
    int maxElement = *std::max_element(arr.begin(), arr.end());

    // Create a boolean vector of size maxElement to mark the existence of numbers
    std::vector<bool> exists(maxElement, false);
    for (int value : arr) {
        // Mark that the number 'value' exists (adjusting for zero-based indexing)
        exists[value - 1] = true;
    }

    // Directly create the compact sorted array by iterating over the 'exists' vector.
    // Since the 'exists' vector indices are in ascending order, the resulting numbers are sorted.
    std::vector<int> sorted;
    for (size_t i = 0; i < exists.size(); i++) {
        if (exists[i]) {
            sorted.push_back(static_cast<int>(i + 1));
        }
    }

    // End the timer after sorting is complete
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Print the compact sorted array
    std::cout << "Compact Sorted Array: ";
    for (int value : sorted) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Output the elapsed time for sorting in microseconds
    std::cout << "Time taken to sort: " << duration.count() << " milliseconds\n";

    return 0;
}
