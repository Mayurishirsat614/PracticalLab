
#include <iostream>
#include <omp.h>
#include <climits>

using namespace std;


void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;  // Initialize min_value to positive infinity


  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] < min_value) {
      min_value = arr[i];  // Update min_value if a smaller element is found
    }
  }

  cout << "Minimum value: " << min_value << endl;
}


void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;  // Initialize max_value to negative infinity

  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
    if (arr[i] > max_value) {
      max_value = arr[i];  // Update max_value if a larger element is found
    }
  }

  cout << "Maximum value: " << max_value << endl;
}


void sum_reduction(int arr[], int n) {
  int sum = 0;

  // Use OpenMP parallel for loop with reduction clause (+)
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add each element to the sum
  }

  cout << "Sum: " << sum << endl;
}


void average_reduction(int arr[], int n) {
  int sum = 0;

  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
    sum += arr[i];  // Add each element to the sum
  }


  double average = (double)sum / (n - 1);
  cout << "Average: " << average << endl;
}

int main() {
  int n;
  cout << "\nEnter the total number of elements: ";
  cin >> n;

  int *arr = new int[n]; // Allocate memory for the array

  cout << "\nEnter the elements: ";
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);

  delete[] arr;  // Deallocate memory after use
  return 0;
}