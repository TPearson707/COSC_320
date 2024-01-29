/*
Author: Don Spickler
Creation Date: 1/25/2024
Last Update: 1/25/2024
Description: Main driver program to allow the user to select array
criteria and a sorting algorithm, then time the sort of the array with
the selected algorithm.
User Interface: User will be asked for the algorithm to use, the
type of data (int or double) if applicable, array size, data value
size if applicable, and to print the array to the console or not.
Notes: Algorithms and code were taken from either
Data Structures and Algorithms in C++ by Adam Drozdek or
Introduction to Algorithms Fourth Edition by Cormen, Leiserson, Rivest, and
Stein
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>

#include "Sorts.h"
#include "timer.h"

using namespace std;

// Prototypes
template <class T> void print(T A[], int size);
template <class T> void outputSorted(T A[], int size);

int sortAlg();
bool getNumericType();
long getArraySize();
int getModulus();
bool getPrintArrays();
pair<double, double> getDoubleRange();

int main() {
  srand(time(0));

  // Array size
  long n = 0;
  // Modulus for integer arrays
  int mod = 1000;
  // Timing begin and end times.
  double start, finish;
  // Print the array
  bool printyn = false;
  // Algorithm number
  int alg = 0;
  // Integer or double data
  bool intdata = true;
  // Double data lower and upper bounds.
  double lower = 0, upper = 1;

  // Array pointers.
  int *A;
  double *B;

  // Get algorithm.
  alg = sortAlg();

  // Get data type to store and sort.
  if (alg == 9 || alg == 10) {
    intdata = true;
  } else if (alg == 11) {
    intdata = false;
  } else {
    intdata = getNumericType();
  }

  // Get the array size.
  n = getArraySize();

  // Get the data bounds.
  if (intdata) {
    mod = getModulus();
  } else if (alg != 11) {
    auto vals = getDoubleRange();
    lower = get<0>(vals);
    upper = get<1>(vals);
  }

  // Print arrays, or not.
  printyn = getPrintArrays();

  if (intdata) {
    // Integer data, declare and populate with random numbers.
    A = new int[n];
    for_each(A, A + n, [mod](int &i) { i = rand() % mod; });

    // Print array
    if (printyn)
      print(A, n);

    // Get start time.
    GET_TIME(start);

    // Sort with selected algorithm.
    if (alg == 1)
      bubble(A, n);
    else if (alg == 2)
      insertion(A, n);
    else if (alg == 3)
      selection(A, n);
    else if (alg == 4)
      mergeSort(A, n);
    else if (alg == 5)
      quickSort(A, n);
    else if (alg == 6)
      combsort(A, n);
    else if (alg == 7)
      Shellsort(A, n);
    else if (alg == 8)
      heapsort(A, n);
    else if (alg == 9)
      radixsort(A, n, 10);
    else if (alg == 10)
      countsort(A, n);
    else if (alg == 12)
      sort(A, A + n);

    // Get end time.
    GET_TIME(finish);

    // Print array
    if (printyn)
      print(A, n);

    // Check sorting and free memory.
    outputSorted(A, n);
    delete[] A;
  } else {
    // Double data, declare and populate with random numbers.
    B = new double[n];
    for_each(B, B + n, [lower, upper](double &i) {
      i = (upper - lower) * rand() / RAND_MAX + lower;
    });

    // Print array.
    if (printyn)
      print(B, n);

    // Get start time.
    GET_TIME(start);

    // Sort with selected algorithm.
    if (alg == 1)
      bubble(B, n);
    else if (alg == 2)
      insertion(B, n);
    else if (alg == 3)
      selection(B, n);
    else if (alg == 4)
      mergeSort(B, n);
    else if (alg == 5)
      quickSort(B, n);
    else if (alg == 6)
      combsort(B, n);
    else if (alg == 7)
      Shellsort(B, n);
    else if (alg == 8)
      heapsort(B, n);
    else if (alg == 11)
      BucketSort(B, n);
    else if (alg == 12)
      sort(B, B + n);

    // Get ending time.
    GET_TIME(finish);

    // Print array.
    if (printyn)
      print(B, n);

    // Check sorting and free memory.
    outputSorted(B, n);
    delete[] B;
  }

  // Report sort time.
  cout << "The sort took " << finish - start << " seconds." << endl;

  return 0;
}

/*
Description: Prints the array to the console.
Parameters: A array and size of the array.
Return: None
*/
template <class T> void print(T A[], int size) {
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << endl;
}

/*
Description: Checks if the array is sorted and outputs the result.
Parameters: A array and size of the array.
Return: None
*/
template <class T> void outputSorted(T A[], int size) {
  if (sorted(A, size))
    cout << "Sorted" << endl;
  else
    cout << "Not Sorted" << endl;
}

/*
Description: Gets the sorting algorithm to use.
Parameters: None
Return: Integer representing the algorithm to use.
*/
int sortAlg() {
  int val = 0;

  cout << "Sorting Algorithm" << endl;
  cout << "1. Bubble Sort" << endl;
  cout << "2. Insertion Sort" << endl;
  cout << "3. Selection Sort" << endl;
  cout << "4. Merge Sort" << endl;
  cout << "5. Quick Sort" << endl;
  cout << "6. Comb Sort" << endl;
  cout << "7. Shell Sort" << endl;
  cout << "8. Heap Sort" << endl;
  cout << "9. Radix Sort" << endl;
  cout << "10. Count Sort" << endl;
  cout << "11. Bucket Sort" << endl;
  cout << "12. Algorithm Library Sort" << endl;

  while (val < 1 || val > 12) {
    cout << "Selection: ";
    cin >> val;
  }

  return val;
}

/*
Description: Gets the data type to use for the arrays.
Parameters: None
Return: Boolean, true for integer and false for double.
*/
bool getNumericType() {
  int type = 0;
  cout << "Data: 1 = int   2 = double: ";
  cin >> type;

  return (type == 1) ? true : false;
}

/*
Description: Gets the array size.
Parameters: None
Return: Long representing the size of the array.
*/
long getArraySize() {
  long n = 0;
  cout << "Input the array size: ";
  cin >> n;

  return n;
}

/*
Description: Gets the modulus to use for integer arrays.
Parameters: None
Return: int representing the data modulus.
*/
int getModulus() {
  int mod = 1000;
  cout << "Input the maximum element size (0 for RAND_MAX): ";
  cin >> mod;

  if (mod == 0)
    mod = RAND_MAX;

  return mod;
}

/*
Description: Gets a boolean to print the arrays or not.
Parameters: None
Return: true to print and false to not.
*/
bool getPrintArrays() {
  char printyn;
  cout << "Print arrays (y/n): ";
  cin >> printyn;

  return (tolower(printyn) == 'y') ? true : false;
}

/*
Description: Gets the data range for double array data.
Parameters: None
Return: pair representing the lower and upper bounds to use
for the data.
*/
pair<double, double> getDoubleRange() {
  double lower, upper;
  cout << "Input lower bound for data range: ";
  cin >> lower;
  cout << "Input upper bound for data range: ";
  cin >> upper;

  return {lower, upper};
}
