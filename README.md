Disclaimer: Program written by ChatGPT 

    BIG SORT - SORT IN CONSTANT TIME! 
               MASSIVE MEMORY OVERHEAD
    ==================================
    ASSUMPTIONS:
    - No duplicate values in the input array.
    - Input contains only positive integers.

    PROGRAM FLOW:
     > create an array (vector) `int arr[]`
     > create sparse presence array (vector) `bool exists[]`, 
       true indicates presence, its index indicates value
     > iterate over exists[] and if true, push the index i 
       into the array (vector) `int sorted[]`

    PERFORMANCE:
    - Time Complexity: O(n + k) (linear, where `k = maxElement`).
    - Space Complexity: O(k) (memory usage scales with the largest 
      element).
