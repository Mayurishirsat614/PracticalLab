/**
 * LAB 2:
 *      Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP.
 *      Use existing algorithms and measure the performance of sequential and parallel algorithms.
 *
 * TO EXECUTE CODE:
 *      >> g++ -fopenmp lab2.cpp
 *      >> ./a
 */

#include <omp.h>
#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;

void displayArray(string, int[], int);
void bubbleSort(int[], int);
void mergeSort(int[], int, int);
void merge(int[], int, int, int, int);

void displayArray(string message, int nums[], int length)
{
    cout << "\t" << message << ": [";
    for (int i = 0; i < length; i++)
    {
        cout << nums[i] << ", ";
    }
    cout << "\b\b]" << endl;
}

void bubbleSort(int nums[], int length)
{
    for (int i = 0; i < length; i++)
    {
        int start = i % 2; // Start from 0 if `i` is even else start from 1.

#pragma omp parallel for
        for (int j = start; j < length - 1; j += 2)
        {
            if (nums[j] > nums[j + 1])
            {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

void mergeSort(int nums[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;

#pragma omp parallel sections num_threads(2)
        {
#pragma omp section
            mergeSort(nums, start, mid);
#pragma omp section
            mergeSort(nums, mid + 1, end);
        }
        merge(nums, start, mid, mid + 1, end);
    }
}

void merge(int nums[], int leftStart, int leftEnd, int rightStart, int rightEnd)
{
    int n = (rightEnd - leftStart) + 1; // Size of both the array
    int tempArray[n];                   // Create temporary array.
    int t = 0;                          // Index for temporary array.
    int l = leftStart;                  // Index for left array.
    int r = rightStart;                 // Index for right array.

    // Put the element from left and right array into tempArray in sorted order.
    while (l <= leftEnd && r <= rightEnd)
    {
        if (nums[l] <= nums[r])
            tempArray[t++] = nums[l++];
        else
            tempArray[t++] = nums[r++];
    }

    // If left array still has few elements yet to add, add them too.
    while (l <= leftEnd)
        tempArray[t++] = nums[l++];

    // If right array still has few elements yet to add, add them too.
    while (r <= rightEnd)
        tempArray[t++] = nums[r++];

    // Copy the elements from tempArray to nums.
    for (int t = 0; t < n; t++)
        nums[leftStart++] = tempArray[t];
}

int main()
{
    // Bubble Sort Example.
    int nums1[] = {4, 6, 2, 0, 7, 6, 1, 9, -3, -5};
    int length1 = sizeof(nums1) / sizeof(int);

    auto start_bubble = high_resolution_clock::now();
    
    cout << "Bubble Sort: " << endl;
    displayArray("Before ", nums1, length1);
    bubbleSort(nums1, length1);
    displayArray("After  ", nums1, length1);

    auto end_bubble = high_resolution_clock::now();
    auto duration_bubble = duration_cast<microseconds>(end_bubble - start_bubble);
    cout << "\nExecution time for Bubble Sort: " << duration_bubble.count() << " microseconds" << endl;
    


    int nums2[] = {3, 5, 1, -1, 6, 5, 0, 8, -2, -4};
    int length2 = sizeof(nums2) / sizeof(int);

    auto start_merge = high_resolution_clock::now();

    cout << "Merge Sort: " << endl;
    displayArray("Before ", nums2, length2);
    mergeSort(nums2, 0, length2 - 1); 
    displayArray("After  ", nums2, length2);

    auto end_merge = high_resolution_clock::now();


    auto duration_merge = duration_cast<microseconds>(end_bubble - start_bubble);
    cout << "\nExecution time for Merge Sort: " << duration_bubble.count() << " microseconds" << endl;
    

    return 0;
}
