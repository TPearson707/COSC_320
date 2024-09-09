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

/*
 * Modified By: Thomas Pearson
 * Date Last Update: 03/15/2024
 */

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

#include "Sorts.h"
#include "timer.h"

using namespace std;

// Prototypes
template <class T> void print(T A[], int size);
template <class T> void outputSorted(T A[], int size);

using sortFncPtr = void (*)(int* A, int n);
using sortDoubleFncPtr = void (*)(double* A, long n);
using sortCountPtr = void(*)(int* A, long n);
using algsortFncPtr = void (*)(int* begin, int* end);
using radixFncPtr = void (*)(int* A, int n, int r);

// void getAverageCase(int* A, int n, sortFncPtr);
void fillArray(int*, int, int);
void fillArray(int*, long, int);
void fillArray(double*, long);
int sortAlg();
bool getNumericType();
long getArraySize();
int getModulus();
bool getPrintArrays();
pair<double, double> getDoubleRange();

int main() {

  sortFncPtr funcPtr;
  algsortFncPtr funcPtr2;
  radixFncPtr funcPtr3;

  srand(time(0));

  // Array size
  long n = 0;
  // Modulus for integer arrays
  int mod = getModulus();
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


    auto getAverageCase = [](int* A, int n, sortFncPtr funcPtr) -> void {
      double start, finish;


      GET_TIME(start);
      funcPtr(A, n);
      GET_TIME(finish);

      double elapsed = finish - start;

      cout << "The sort took " << elapsed << " seconds." << endl;
    };

    auto getAlgSortAvg = [](int*  begin, int* end, algsortFncPtr funcPtr) -> void {
      double start, finish;

      GET_TIME(start);
      funcPtr(begin, end);
      GET_TIME(finish)

      double elapsed = finish - start;

      cout << "The sort took " << elapsed << " seconds." << endl;
    };

    auto getRadixAvg = [](int*  A, int n, int r, radixFncPtr funcPtr) -> void {
      double start, finish;

      GET_TIME(start);
      funcPtr(A, n, r);
      GET_TIME(finish)

      double elapsed = finish - start;

      cout << "The sort took " << elapsed << " seconds." << endl;
    };

    // Integer data, declare and populate with random numbers.


    int n1 = 10000000;
    int n2 = 50000000;
    int n3 = 100000000;
    int n4 = 150000000;
    int n5 = 200000000;
    int n6 = 250000000;
    int n7 = 300000000;
    int n8 = 350000000;
    int n9 = 400000000;
    int n10 = 450000000;

    int* A = new int[n1];
    int* B = new int[n2];
    int* C = new int[n3];
    int* D = new int[n4];
    int* E = new int[n5];
    int* F = new int[n6];
    int* G = new int[n7];
    int* H = new int[n8];
    int* I = new int[n9];
    int* J = new int[n10];

    // merge, qiuck, comb, shell, heap
    for (int i = 5; i < 5; i++) {

      switch(i) {
        case 0:
          funcPtr = mergeSort;
          cout << "Testing MergeSort" << endl;
          break;
        case 1:
          funcPtr = quickSort;
          cout << "Testing QiuckSort" << endl;
          break;
        case 2:
          funcPtr = combsort;
          cout << "Testing CombSort" << endl;
          break;
        case 3:
          funcPtr = Shellsort;
          cout << "Testing ShellSort" << endl;
          break;
        case 4:
          funcPtr = heapsort;
          cout << "Testing HeapSort" << endl;
          break;
      }

      fillArray(A, n1, mod);
      fillArray(B, n2, mod);
      fillArray(C, n3, mod);
      fillArray(D, n4, mod);
      fillArray(E, n5, mod);
      fillArray(F, n6, mod);
      fillArray(G, n7, mod);
      fillArray(H, n8, mod);
      fillArray(I, n9, mod);
      fillArray(J, n10, mod);

      cout << "Size: " << n1 << " ";
      getAverageCase(A, n1, funcPtr);
      cout << "Size: " << n2 << " ";
      getAverageCase(B, n2, funcPtr);
      cout << "Size: " << n3 << " ";
      getAverageCase(C, n3, funcPtr);
      cout << "Size: " << n4 << " ";
      getAverageCase(D, n4, funcPtr);
      cout << "Size: " << n5 << " ";
      getAverageCase(E, n5, funcPtr);
      cout << "Size: " << n6 << " ";
      getAverageCase(F, n6, funcPtr);
      cout << "Size: " << n7 << " ";
      getAverageCase(G, n7, funcPtr);
      cout << "Size: " << n8 << " ";
      getAverageCase(H, n8, funcPtr);
      cout << "Size: " << n9 << " ";
      getAverageCase(I, n9, funcPtr);
      cout << "Size: " << n10 << " ";
      getAverageCase(J, n10, funcPtr);

      cout << endl << endl;
    }

  cout << "Testing Algorithm Library Sort" << endl;

  fillArray(A, n1, mod);
  fillArray(B, n2, mod);
  fillArray(C, n3, mod);
  fillArray(D, n4, mod);
  fillArray(E, n5, mod);
  fillArray(F, n6, mod);
  fillArray(G, n7, mod);
  fillArray(H, n8, mod);
  fillArray(I, n9, mod);
  fillArray(J, n10, mod);

  cout << "Size: " << n1 << " ";
  getAlgSortAvg(A, A + n1, sort);
  cout << "Size: " << n2 << " ";
  getAlgSortAvg(B, B + n2, sort);
  cout << "Size: " << n3 << " ";
  getAlgSortAvg(C, C + n3, sort);
  cout << "Size: " << n4 << " ";
  getAlgSortAvg(D, D + n4, sort);
  cout << "Size: " << n5 << " ";
  getAlgSortAvg(E, E + n5, sort);
  cout << "Size: " << n6 << " ";
  getAlgSortAvg(F, F + n6, sort);
  cout << "Size: " << n7 << " ";
  getAlgSortAvg(G, G + n7, sort);
  cout << "Size: " << n8 << " ";
  getAlgSortAvg(H, H + n8, sort);
  cout << "Size: " << n9 << " ";
  getAlgSortAvg(I, I + n9, sort);
  cout << "Size: " << n10 << " ";
  getAlgSortAvg(J, J + n10, sort);

  cout << endl << endl;


  cout << "Testing Radix Sort" << endl;
  for (int i = 0; i < 7; i++) {

    funcPtr3 = radixsort;
    int radix = 10;
    int mod = 1000;
    if (i < 4) {
      fillArray(A, n1, RAND_MAX);
      fillArray(B, n2, RAND_MAX);
      fillArray(C, n3, RAND_MAX);
      fillArray(D, n4, RAND_MAX);
      fillArray(E, n5, RAND_MAX);
      fillArray(F, n6, RAND_MAX);
      fillArray(G, n7, RAND_MAX);
      fillArray(H, n8, RAND_MAX);
      fillArray(I, n9, RAND_MAX);
      fillArray(J, n10, RAND_MAX);
    } else {
      fillArray(A, n1, mod);
      fillArray(B, n2, mod);
      fillArray(C, n3, mod);
      fillArray(D, n4, mod);
      fillArray(E, n5, mod);
      fillArray(F, n6, mod);
      fillArray(G, n7, mod);
      fillArray(H, n8, mod);
      fillArray(I, n9, mod);
      fillArray(J, n10, mod);
    }
    switch(i) {
      case 0:
        cout << "Testing with radix 10, RAND_MAX" << endl;
        radix = 10;
        break;
      case 1:
         cout << "Testing with radix 100, RAND_MAX" << endl;
        radix = 100;
        break;
      case 2:
         cout << "Testing with radix 1000, RAND_MAX" << endl;
        radix = 1000;
        break;
      case 3:
         cout << "Testing with radix 10000, RAND_MAX" << endl;
        radix = 10000;
        break;
      case 4:
        cout << "Testing with radix 10, 0 to 1000" << endl;
        radix = 10;
        break;
      case 5:
        cout << "Testing with radix 100, 0, to 1000" << endl;
        radix = 100;
        break;
      case 6:
        cout << "Testing with radix 1000, 0, to 1000" << endl;
        radix = 1000;
        break;
    }

    cout << "Size: " << n1 << " ";
    getRadixAvg(A, n1, radix, funcPtr3);
    cout << "Size: " << n2 << " ";
    getRadixAvg(B, n2, radix, funcPtr3);
    cout << "Size: " << n3 << " ";
    getRadixAvg(C, n3, radix, funcPtr3);
    cout << "Size: " << n4 << " ";
    getRadixAvg(D, n4, radix, funcPtr3);
    cout << "Size: " << n5 << " ";
    getRadixAvg(E, n5, radix, funcPtr3);
    cout << "Size: " << n6 << " ";
    getRadixAvg(F, n6, radix, funcPtr3);
    cout << "Size: " << n7 << " ";
    getRadixAvg(G, n7, radix, funcPtr3);
    cout << "Size: " << n8 << " ";
    getRadixAvg(H, n8, radix, funcPtr3);
    cout << "Size: " << n9 << " ";
    getRadixAvg(I, n9, radix, funcPtr3);
    cout << "Size: " << n10 << " ";
    getRadixAvg(J, n10, radix, funcPtr3);

    cout << endl << endl;
  }


    auto getCountAverage = [](int* A, long n, sortCountPtr funcPtr) -> void {
      double start, finish;

      GET_TIME(start);
      funcPtr(A, n);
      GET_TIME(finish);

      double elapsed = finish - start;

      cout << "The sort took " << elapsed << " seconds." << endl;
    };

    long n1l = 10000000;
    long n2l = 50000000;
    long n3l = 100000000;
    long n4l = 150000000;
    long n5l = 200000000;
    long n6l = 250000000;
    long n7l = 300000000;
    long n8l = 350000000;
    long n9l = 400000000;
    long n10l = 450000000;

    delete[] J;
    cout << "Testing Count Sort" << endl;

    fillArray(J, n10l, RAND_MAX);

    cout << "Size: " << n1l << " ";
    getCountAverage(J, n1l, countsort);

    fillArray(J, n1l, RAND_MAX);

    cout << "Size: " << n2l << " ";
    getCountAverage(J, n2l, countsort);

    fillArray(J, n2l, RAND_MAX);

    cout << "Size: " << n3l << " ";
    getCountAverage(J, n3l, countsort);

    fillArray(J, n3l, RAND_MAX);

    cout << "Size: " << n4l << " ";
    getCountAverage(J, n4l, countsort);

    fillArray(J, n4l, RAND_MAX);

    cout << "Size: " << n5l << " ";
    getCountAverage(J, n5l, countsort);

    fillArray(J, n5l, RAND_MAX);

    cout << "Size: " << n6l << " ";
    getCountAverage(J, n6l, countsort);

    fillArray(J, n6l, RAND_MAX);

    cout << "Size: " << n7l << " ";
    getCountAverage(J, n7l, countsort);

    fillArray(J, n7l, RAND_MAX);

    cout << "Size: " << n8l << " ";
    getCountAverage(J, n8l, countsort);

    fillArray(J, n8l, RAND_MAX);

    cout << "Size: " << n9l << " ";
    getCountAverage(J, n9l, countsort);

    fillArray(J, n9l, RAND_MAX);

    cout << "Size: " << n10l << " ";
    getCountAverage(J, n10l, countsort);

    cout << endl << endl;

    fillArray(J, n10l, 1000);

    cout << "Size: " << n1l << " ";
    getCountAverage(J, n1l, countsort);

    fillArray(J, n1l, 1000);

    cout << "Size: " << n2l << " ";
    getCountAverage(J, n2l, countsort);

    fillArray(J, n2l, 1000);

    cout << "Size: " << n3l << " ";
    getCountAverage(J, n3l, countsort);

    fillArray(J, n3l, 1000);

    cout << "Size: " << n4l << " ";
    getCountAverage(J, n4l, countsort);

    fillArray(J, n4l, 1000);

    cout << "Size: " << n5l << " ";
    getCountAverage(J, n5l, countsort);

    fillArray(J, n5l, 1000);

    cout << "Size: " << n6l << " ";
    getCountAverage(J, n6l, countsort);

    fillArray(J, n6l, 1000);

    cout << "Size: " << n7l << " ";
    getCountAverage(J, n7l, countsort);

    fillArray(J, n7l, 1000);

    cout << "Size: " << n8l << " ";
    getCountAverage(J, n8l, countsort);

    fillArray(J, n8l, 1000);

    cout << "Size: " << n9l << " ";
    getCountAverage(J, n9l, countsort);

    fillArray(J, n9l, 1000);

    cout << "Size: " << n10l << " ";
    getCountAverage(J, n10l, countsort);

    cout << endl << endl;

    outputSorted(A, n1);
    delete[] A;
    outputSorted(B, n2);
    delete[] B;
    outputSorted(C, n3);
    delete[] C;
    outputSorted(D, n4);
    delete[] D;
    outputSorted(E, n5);
    delete[] E;
    outputSorted(F, n6);
    delete[] F;
    outputSorted(G, n7);
    delete[] G;
    outputSorted(H, n8);
    delete[] H;
    outputSorted(I, n9);
    delete[] I;
    outputSorted(J, n10);
    delete[] J;

    double* Jd = new double[n10];

    auto getBucketAverage = [](double* A, long n, sortDoubleFncPtr funcPtr) -> void {
      double start, finish;

      GET_TIME(start);
      funcPtr(A, n);
      GET_TIME(finish);

      double elapsed = finish - start;

      cout << "The sort took " << elapsed << " seconds." << endl;
    };

    cout << "Testing Bucket Sort" << endl;
    sortDoubleFncPtr funcPtr4 = BucketSort;

    fillArray(Jd, n10l);

    cout << "Size: " << n1l << " ";
    getBucketAverage(Jd, n1l, BucketSort);

    fillArray(Jd, n1l);

    cout << "Size: " << n2l << " ";
    getBucketAverage(Jd, n2l, BucketSort);

    fillArray(Jd, n2l);

    cout << "Size: " << n3l << " ";
    getBucketAverage(Jd, n3l, BucketSort);

    fillArray(Jd, n3l);

    cout << "Size: " << n4l << " ";
    getBucketAverage(Jd, n4l, BucketSort);

    fillArray(Jd, n4l);

    cout << "Size: " << n5l << " ";
    getBucketAverage(Jd, n5l, BucketSort);

    fillArray(Jd, n5l);

    cout << "Size: " << n6l << " ";
    getBucketAverage(Jd, n6l, BucketSort);

    fillArray(Jd, n6l);

    cout << "Size: " << n7l << " ";
    getBucketAverage(Jd, n7l, BucketSort);

    fillArray(Jd, n7l);

    cout << "Size: " << n8l << " ";
    getBucketAverage(Jd, n8l, BucketSort);

    fillArray(Jd, n8l);

    cout << "Size: " << n9l << " ";
    getBucketAverage(Jd, n9l, BucketSort);

    fillArray(Jd, n9l);

    cout << "Size: " << n10l << " ";
    getBucketAverage(Jd, n10l, BucketSort);

    // Check sorting and free memory.

    outputSorted(Jd, n10);
    delete[] Jd;

  return 0;
}

/*
 * Description: fillArray function for sorts
 * Parameters: int* A, int n, int mod
 * Return Type: void
 */
void fillArray(int* A, int n, int mod) {
  for_each(A, A + n, [mod](int &i) { i = rand() % mod; });
}

/*
 * Description: Overloaded fillArray function for countsort
 * Parameters: int* A, long n, int mod
 * Return Type: void
 */
void fillArray(int* A, long n, int mod) {
  for_each(A, A + n, [mod](int &i) { i = rand() % mod; });
}

/*
 * Description: Overloaded fillArray function for bucketSort
 * Parameters: double* A, long n
 * Return Type: void
 */
void fillArray(double* B, long n) {
    int lower = 0;
    int upper = 1;

    for_each(B, B + n, [lower, upper](double &i) {
      i = (upper - lower) * rand() / RAND_MAX + lower;
    });
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
