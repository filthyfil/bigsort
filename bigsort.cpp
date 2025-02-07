#include <iostream>
#include <vector>
#include <cstdlib>      // For exit()
#include <algorithm>    // For std::max_element and std::shuffle
#include <chrono>       // For high-resolution timing
#include <random>       // For random number generation

// ============================================================
// Class: RandomArrayGenerator
// ------------------------------------------------------------
// Role: Provides a static method to generate a unique random
//       array (vector) of integers within a specified range.
//       This class encapsulates the logic for creating and
//       shuffling a full range of numbers, then selecting the
//       desired count.
// ============================================================
class RandomArrayGenerator {
public:
    // ------------------------------------------------------------
    // Method: generateUniqueRandomArray
    // ------------------------------------------------------------
    // Parameters:
    //   - size: Number of unique random integers to generate.
    //   - minValue: The minimum possible value in the range.
    //   - maxValue: The maximum possible value in the range.
    //
    // Returns:
    //   A vector of integers of the given size, containing unique
    //   random values from [minValue, maxValue].
    //
    // Flow:
    //   1. Check if the range is sufficient for the requested size.
    //   2. Create a vector containing all numbers from minValue to maxValue.
    //   3. Shuffle the vector using a modern random generator.
    //   4. Return the first 'size' numbers from the shuffled vector.
    // ------------------------------------------------------------
    static std::vector<int> generateUniqueRandomArray(int size, int minValue, int maxValue) {
        int range = maxValue - minValue + 1;
        if (size > range) {
            std::cerr << "Error: Array size cannot be larger than the number of unique values in the range.\n";
            exit(1);
        }

        // Step 2: Populate a vector with all numbers in the range.
        std::vector<int> allNumbers;
        allNumbers.reserve(range);
        for (int num = minValue; num <= maxValue; ++num) {
            allNumbers.push_back(num);
        }
        
        // Step 3: Shuffle the vector using a modern random generator.
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(allNumbers.begin(), allNumbers.end(), g);
        
        // Step 4: Build the resulting array by taking the first 'size' numbers.
        std::vector<int> arr;
        arr.reserve(size);
        for (int i = 0; i < size; ++i) {
            arr.push_back(allNumbers[i]);
        }
        return arr;
    }
};

// ============================================================
// Class: BigSorter
// ------------------------------------------------------------
// Role: Implements the "Big Sort" algorithm, which sorts an
//       array in linear time using a sparse presence vector.
//       It also measures the time taken to perform the sort.
// ============================================================
class BigSorter {
public:
    // ------------------------------------------------------------
    // Constructor: BigSorter
    // ------------------------------------------------------------
    // Parameters:
    //   - inputArray: The unsorted array to be processed.
    //
    // Role:
    //   Stores the original array and initializes timing and
    //   internal state variables.
    // ------------------------------------------------------------
    BigSorter(const std::vector<int>& inputArray)
        : originalArray(inputArray), sortDurationMs(0), existsArraySize(0) { }

    // ------------------------------------------------------------
    // Method: sort
    // ------------------------------------------------------------
    // Role:
    //   Performs the "Big Sort" algorithm which:
    //     1. Finds the maximum element to determine the size of a
    //        boolean "exists" vector.
    //     2. Marks the presence of each number in the boolean vector.
    //     3. Iterates through the boolean vector to build a compact,
    //        sorted array.
    //     4. Measures and records the time taken for this sorting process.
    // ------------------------------------------------------------
    void sort() {
        using Clock = std::chrono::high_resolution_clock;
        auto startTime = Clock::now();

        // Step 1: Determine the maximum element in the array.
        int maxElement = *std::max_element(originalArray.begin(), originalArray.end());
        existsArraySize = maxElement; // 'exists' vector will have a size equal to the maximum element.

        // Step 2: Create and populate a boolean vector indicating number presence.
        std::vector<bool> exists(existsArraySize, false);
        for (int value : originalArray) {
            exists[value - 1] = true; // Adjust index for zero-based vector.
        }

        // Step 3: Build the sorted array by iterating over the 'exists' vector.
        sortedArray.clear();
        sortedArray.reserve(originalArray.size());
        for (size_t i = 0; i < exists.size(); ++i) {
            if (exists[i]) {
                sortedArray.push_back(static_cast<int>(i + 1)); // Adjust index back.
            }
        }

        // Step 4: Record the elapsed time for the sort operation.
        auto endTime = Clock::now();
        sortDurationMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    }

    // ------------------------------------------------------------
    // Accessor: getSortedArray
    // ------------------------------------------------------------
    // Returns:
    //   A constant reference to the sorted array.
    // ------------------------------------------------------------
    const std::vector<int>& getSortedArray() const { return sortedArray; }

    // ------------------------------------------------------------
    // Accessor: getSortDurationMs
    // ------------------------------------------------------------
    // Returns:
    //   The time taken (in milliseconds) to perform the sorting.
    // ------------------------------------------------------------
    long long getSortDurationMs() const { return sortDurationMs; }

    // ------------------------------------------------------------
    // Accessor: getOriginalArraySize
    // ------------------------------------------------------------
    // Returns:
    //   The number of elements in the original unsorted array.
    // ------------------------------------------------------------
    int getOriginalArraySize() const { return static_cast<int>(originalArray.size()); }

    // ------------------------------------------------------------
    // Accessor: getExistsArraySize
    // ------------------------------------------------------------
    // Returns:
    //   The size of the boolean "exists" vector used during sorting.
    // ------------------------------------------------------------
    int getExistsArraySize() const { return existsArraySize; }

private:
    std::vector<int> originalArray;  // The original unsorted array.
    std::vector<int> sortedArray;    // The resulting sorted array.
    long long sortDurationMs;        // Time taken for sorting in milliseconds.
    int existsArraySize;             // Size of the boolean "exists" vector.
};

// ============================================================
// Function: main
// ------------------------------------------------------------
// Role: Orchestrates the overall program flow:
//       1. Gathers user input for the array size and maximum value.
//       2. Generates a unique random array using RandomArrayGenerator.
//       3. Displays the original unsorted array.
//       4. Instantiates BigSorter to sort the array and measure sorting time.
//       5. Displays the sorted array and timing details.
// ------------------------------------------------------------
int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    int max;
    std::cout << "Enter max element value: ";
    std::cin >> max;

    // Validate that the array size does not exceed the range of unique values.
    if (size > max) {
        std::cerr << "Error: Array size (" << size 
                  << ") is greater than the number of unique values in the range [1, " << max << "].\n";
        return 1;
    }

    // Step 1 & 2: Generate the original unsorted array with unique random values.
    std::vector<int> arr = RandomArrayGenerator::generateUniqueRandomArray(size, 1, max);

    // Step 3: Print the original unsorted array.
    std::cout << "Original Array: ";
    for (int value : arr) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Step 4: Create an instance of BigSorter to perform the sort.
    BigSorter sorter(arr);
    sorter.sort();

    // Retrieve the sorted array.
    const std::vector<int>& sorted = sorter.getSortedArray();

    // Step 5: Display the sorted array.
    std::cout << "Compact Sorted Array: ";
    for (int value : sorted) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Display additional performance details.
    std::cout << "Original array size: " << sorter.getOriginalArraySize() << "\n";
    std::cout << "Exists array size: " << sorter.getExistsArraySize() << "\n";
    std::cout << "Sorted array size: " << sorted.size() << "\n";
    std::cout << "Time taken to sort: " << sorter.getSortDurationMs() << " milliseconds\n";

    return 0;
}
