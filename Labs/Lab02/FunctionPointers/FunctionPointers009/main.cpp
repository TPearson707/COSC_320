/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Some more advanced examples of using function pointers.
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// Defines a YesNoFcn as a pointer to a function bringing in two ints and
// outputs a bool.
typedef bool (*YesNoFcn)(int, int);

template <class T> using boolfct = bool (*)(T, T);
template <class T, class R> using fctp = R (*)(T, T);
template <class T> using updater = void (*)(T &);
template <class T> using updaterrt = T (*)(T);

// Prototypes
bool intEqual(int, int);
bool intGreater(int, int);
bool bothOdd(int, int);
void randupdate(int &i);
template <class T> void print(T &a);
template <class T> void printArray(T A[], int sz);

int ToUpper(int ch) { return toupper(ch); }

int main() {
  srand(time(0));

  // Declares a dynamic array of pointers to functions with
  // two int input parameters and a double output.
  fctp<int, double> *A2 = new fctp<int, double>[25];

  // A vector of function pointers to functions with
  // two int input parameters and a bool output.
  vector<bool (*)(int, int)> vect;
  vect.push_back(intEqual);
  vect.push_back(bothOdd);
  vect.push_back(intGreater);

  // Same structure as vect;
  vector<YesNoFcn> vect2;
  vect2.push_back(intEqual);
  vect2.push_back(bothOdd);
  vect2.push_back(intGreater);

  // Declaration of a function pointer to a function with
  // two int input parameters and a bool output.
  boolfct<int> bf;
  bf = intEqual;

  // Declaration of a function pointer to a function with
  // two int input parameters and a bool output.
  fctp<int, bool> fct;
  fct = intGreater;

  // Vector of function pointers to functions with two
  // double inputs and an int output.
  vector<fctp<double, int>> vect3;

  // Use of function pointers in some algorithm library
  // functions.
  int *A = new int[10];
  int sz = 10;
  for_each(A, A + sz, randupdate);
  for_each(A, A + sz, print<int>);
  cout << endl;

  // less and greater are predefined templated functions from the STL.
  sort(A, A + sz, less());
  printArray(A, sz);

  sort(A, A + sz, greater());
  printArray(A, sz);

  updater<int> updatefct = randupdate;
  for_each(A, A + sz, updatefct);
  printArray(A, sz);

  string str = "Examples of Function Pointers";
  cout << str << endl;

  transform(str.begin(), str.end(), str.begin(), ::toupper);
  cout << str << endl;

  transform(str.begin(), str.end(), str.begin(), ::tolower);
  cout << str << endl;

  transform(str.begin(), str.end(), str.begin(), ToUpper);
  cout << str << endl;

  transform(str.begin(), str.end(), str.begin(), ::tolower);
  cout << str << endl;

  updaterrt<int> updateupper = ::toupper;
  transform(str.begin(), str.end(), str.begin(), updateupper);
  cout << str << endl;

  delete[] A;
  delete[] A2;

  return 0;
}

/*
Description: Replaces i with a random number in [0, 99].
Parameters: i
Return: None
Note: i is an output parameter, standard format for an updater function.
*/

void randupdate(int &i) { i = rand() % 100; }

/*
Description: Prints out the value of the parameter.
Parameters: a
Return: None
*/

template <class T> void print(T &a) { cout << a << " "; }

/*
Description: Prints the array on a single line.
Parameters: Array A and size sz.
Return: None
*/

template <class T> void printArray(T A[], int sz) {
  for_each(A, A + sz, print<T>);
  cout << endl;
}

/*
Description: Function that returns true if both input integers are equal and
false otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if both input integers are equal and false otherwise.
*/

bool intEqual(int inItem1, int inItem2) { return (inItem1 == inItem2); }

/*
Description: Function that returns true if inItem1 > inItem2 and false
otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if inItem1 > inItem2 and false otherwise.
*/

bool intGreater(int inItem1, int inItem2) { return (inItem1 > inItem2); }

/*
Description: Function that returns true if both inItem1 and inItem2 are odd and
false otherwise.
Parameters: inItem1, inItem2: two input integers.
Return: true if both inItem1 and inItem2 and odd and false otherwise.
*/

bool bothOdd(int inItem1, int inItem2) {
  return (inItem1 % 2 == 1 && inItem2 % 2 == 1);
}
