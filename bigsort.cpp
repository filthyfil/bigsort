/*
    BIG SORT - SORT IN CONSTANT TIME! 
    ==================================
    ASSUMPTIONS:
    - No duplicate values in the input array.
    - Input contains only positive integers.

    PROGRAM FLOW:
     > Create a vector `arr` containing unique random integers from the range [minValue, maxValue].
     > Create a sparse presence vector `exists` (of bools) where each index indicates the number’s presence.
     > Iterate over exists[] and if true, push the index (adjusted) into the vector `sorted`.

    PERFORMANCE:
    - Time Complexity: O(n + k) (linear, where k = maxElement).
    - Space Complexity: O(k) (memory usage scales with the largest element).
*/

#include <iostream>
#include <vector>
#include <cstdlib>      // For srand()
#include <ctime>        // For time()
#include <algorithm>    // For std::max_element, std::shuffle
#include <chrono>       // For high-resolution timer
#include <random>       // For std::random_device and std::mt19937

// Function to generate a unique random array (vector) of given size with values in [minValue, maxValue]
void generateUniqueRandomArray(std::vector<int>& arr, int minValue, int maxValue) {
    int range = maxValue - minValue + 1;
    if (arr.size() > static_cast<size_t>(range)) {
        std::cerr << "Error: Array size cannot be larger than the number of unique values in the range.\n";
        exit(1);
    }

    // Create a vector containing the entire range of numbers.
    std::vector<int> allNumbers;
    allNumbers.reserve(range);
    for (int num = minValue; num <= maxValue; num++) {
        allNumbers.push_back(num);
    }
    
    // Shuffle the vector using a modern random generator.
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(allNumbers.begin(), allNumbers.end(), g);
    
    // Fill 'arr' with the first arr.size() numbers from the shuffled list.
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = allNumbers[i];
    }
}

int main() {
    // Seed the C library random number generator (only needed if using rand(), here we use std::shuffle).
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    int max;
    std::cout << "Enter max element value: ";
    std::cin >> max;

    // Ensure that the range is large enough to provide unique values.
    if (size > (max - 1 + 1)) {
        std::cerr << "Error: Array size (" << size 
                  << ") is greater than the number of unique values in the range [1, " << max << "].\n";
        return 1;
    }

    // Create and fill the original array with unique random values.
    std::vector<int> arr(size);
    generateUniqueRandomArray(arr, 1, max);

    // Print the original array
    std::cout << "Original Array: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Start the timer (timing the sorting process)
    auto startTime = std::chrono::high_resolution_clock::now();

    // Find the maximum element in the original array.
    // (Since there are no duplicates and the values come from [1, max], maxElement should be <= max.)
    int maxElement = *std::max_element(arr.begin(), arr.end());

    // Create a boolean vector of size maxElement to mark the presence of numbers.
    std::vector<bool> exists(maxElement, false);
    for (int value : arr) {
        // Mark the number's existence (adjusting for zero-based indexing)
        exists[value - 1] = true;
    }

    // Create the compact sorted array by iterating over the 'exists' vector.
    // Since the indices are processed in order, the resulting array is sorted.
    std::vector<int> sorted;
    sorted.reserve(arr.size());
    for (size_t i = 0; i < exists.size(); i++) {
        if (exists[i]) {
            sorted.push_back(static_cast<int>(i + 1));
        }
    }

    // End the timer after sorting is complete.
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    // Print the compact sorted array.
    std::cout << "Compact Sorted Array: ";
    for (int value : sorted) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Original array size: " << arr.size() << '\n';
    std::cout << "Exists array size: " << exists.size() << '\n';
    std::cout << "Sorted array size: " << sorted.size() << '\n';
    std::cout << "Time taken to sort: " << duration.count() << " milliseconds\n";

    return 0;
}
