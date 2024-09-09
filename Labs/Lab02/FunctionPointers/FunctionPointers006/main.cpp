/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Example of using a function pointer as a parameter to STL functions
from the algorithm library.
User Interface: Program will ask user for the size of the array to sort.
*/

#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

/*
Description: Relational functions similar to function overrides.
Parameters: x, y: Type T elements to be compared.
Return: boolean result from the comparison.
*/

template <class T> bool cmpasc(const T &x, const T &y) { return x < y; }
template <class T> bool cmpdec(const T &x, const T &y) { return x > y; }
template <class T> bool shuffle(const T &x, const T &y) {return rand() % 2;}

int main() {
  srand(time(0));

  // Size of the array to sort.
  int trials = 0;

  cout << "Input the number of values to store: ";
  cin >> trials;

  // Array to be sorted.
  int *A = new int[trials];

  for (int i = 0; i < trials; i++)
    A[i] = rand() % 1000;

  // Print array.
  for (int i = 0; i < trials; i++)
    cout << A[i] << " ";
  cout << endl;

  // Sort ascending.
  sort(A, A + trials, cmpasc<int>);

  // Print array.
  for (int i = 0; i < trials; i++)
    cout << A[i] << " ";
  cout << endl;

  // Sort descending.
  sort(A, A + trials, cmpdec<int>);

  // Print array.
  for (int i = 0; i < trials; i++)
    cout << A[i] << " ";
  cout << endl;

  sort(A, A + trials, shuffle<int>);

  for (int i = 0; i < trials; i++)
    cout << A[i] << " ";
  cout << endl;

  delete[] A;
  return 0;
}
