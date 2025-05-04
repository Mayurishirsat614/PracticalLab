/**
 * Lab 3:
 *      Implement Min, Max, Sum and Average operations using Parallel Reduction.
 *
 * TO EXECUTE CODE:
 *      >> g++ -fopenmp lab3.cpp
 *      >> ./a
 */

#include <omp.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;
using namespace std;


void displayArray(int nums[], int length)
{
    cout << "Nums: [";
    for (int i = 0; i < length; i++)
        cout << nums[i] << ", ";
    cout << "\b\b]" << endl;
}

void minOperation(int nums[], int length)
{
    int minValue = nums[0];

#pragma omp parallel for reduction(min : minValue)
    for (int i = 0; i < length; i++)
        minValue = min(minValue, nums[i]);
    cout << "Min value: " << minValue << endl;
}

void maxOperation(int nums[], int length)
{
    int maxValue = nums[0];

#pragma omp parallel for reduction(max : maxValue)
    for (int i = 0; i < length; i++)
        maxValue = max(maxValue, nums[i]);
    cout << "Max value: " << maxValue << endl;
}

void sumOperation(int nums[], int length)
{
    int sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++)
        sum += nums[i];
    cout << "Sum: " << sum << endl;
}

void avgOperation(int nums[], int length)
{
    float sum = 0;

#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++)
        sum += nums[i];
    cout << "Average: " << (sum / length) << endl;
}

int main()
{
    int nums[] = {4, 6, 3, 2, 6, 7, 9, 2, 1, 6, 5};
    int length = sizeof(nums) / sizeof(int);

    auto start = high_resolution_clock::now();


    displayArray(nums, length);

    minOperation(nums, length); // Parallel Reduction: Min operation
    maxOperation(nums, length); // Parallel Reduction: Max operation
    sumOperation(nums, length); // Parallel Reduction: Sum operation
    avgOperation(nums, length); // Parallel Reduction: Average operation

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop-start);
    cout << "\nExecution time: " << duration.count() << " microseconds" << endl;
    return 0;
}