/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Example of using a function pointer as a parameter.
User Interface: Program will ask user for the size of the array to sort.
*/

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

// Prototypes.

template <class T> void bubbleSort(T[], int);
template <class T> void selectionSort(T[], int);
template <class T> void insertionSort(T[], int);
template <class T> void timeSort(T A[], int s, void (*fctptr)(T[], int));

int main() {
  srand(time(0));

  // Size of the array to sort.
  int trials = 0;

  cout << "Input the number of values to store: ";
  cin >> trials;

  // Vector to store the original random data and array for sorting.
  vector<int> data;
  int *A = new int[trials];

  vector<void (*)(int[], int)> sortAlgs;
  sortAlgs.push_back(bubbleSort);
  sortAlgs.push_back(selectionSort);
  sortAlgs.push_back(insertionSort);

  // Populate vector with random values.
  for (int i = 0; i < trials; i++)
    data.push_back(rand());

  for (int i = 0; i < sortAlgs.size(); i++) {
    copy(data.begin(), data.end(), A);
    timeSort(A, trials, sortAlgs[i]);
  }

//   copy(data.begin(), data.end(), A);
//   timeSort(A, trials, bubbleSort);
//
//   copy(data.begin(), data.end(), A);
//   timeSort(A, trials, selectionSort);
//
//   copy(data.begin(), data.end(), A);
//   timeSort(A, trials, insertionSort);

  delete[] A;
  return 0;
}

/*
Description: Sorting and timing function wrapper.
Parameters: A: array of templated type to be sorted.
s: integer size of the array.
fctptr: Pointer to a function taking in an array and size and no return.
Return: None
*/

template <class T> void timeSort(T A[], int s, void (*fctptr)(T[], int)) {
  auto start = high_resolution_clock::now();
  fctptr(A, s);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time to sort: " << duration.count() / 1000000.0 << " seconds"
       << endl;
}

/*
Description: Array sort using bubble sort algorithm.
Parameters: array: array of templated type to be sorted.
size: integer size of the array.
Return: None
Notes: Type T needs to overload > and assignment.
*/

template <class T> void bubbleSort(T array[], int size) {
  int index;

  for (int maxElement = size - 1; maxElement > 0; maxElement--)
    for (index = 0; index < maxElement; index++)
      if (array[index] > array[index + 1])
        swap(array[index], array[index + 1]);
}

/*
Description: Array sort using selection sort algorithm.
Parameters: array: array of templated type to be sorted.
size: integer size of the array.
Return: None
Notes: Type T needs to overload < and assignment.
*/

template <class T> void selectionSort(T array[], int size) {
  int minIndex;

  for (int start = 0; start < (size - 1); start++) {
    minIndex = start;
    for (int index = start + 1; index < size; index++)
      if (array[index] < array[minIndex])
        minIndex = index;

    swap(array[minIndex], array[start]);
  }
}

/*
Description: Array sort using insertion sort algorithm.
Parameters: array: array of templated type to be sorted.
size: integer size of the array.
Return: None
Notes: Type T needs to overload > and assignment.
*/

template <class T> void insertionSort(T array[], int size) {
  for (int itemsSorted = 1; itemsSorted < size; itemsSorted++) {
    T temp = array[itemsSorted];
    int loc = itemsSorted - 1;
    while (loc >= 0 && array[loc] > temp) {
      array[loc + 1] = array[loc];
      loc = loc - 1;
    }
    array[loc + 1] = temp;
  }
}
