/*
Author: Don Spickler
Creation Date: 1/23/2024
Last Update: 1/23/2024
Description: Example of using lambda expressions in C++.
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

// Prototypes
template <class T> void print(T &i);
template <class T> void printArray(T A[], int sz);
template <class T> void printVector(vector<T> A);

int main() {
  srand(time(0));

  // Example variables.
  int a = 4;
  int b = 5;
  int c = 6;

  // Standard declaration: capture list, parameters, return type (trailing),
  // function body.
  auto f = [a, &b](int x) -> int {
    b += a * x;
    return a - x;
  };

  cout << f(3) << endl;
  cout << a << endl;
  cout << b << endl;

  /* Error: c is not in the capture list.
  auto g = [a, &b](int x) -> int {
    b += a * x + c;
    return a - x;
  };
  // */

  // C++ 14: auto parameters allowed, and return type is deduced.
  auto add = [](auto x, auto y) { return x + y; };

  cout << add(5, 7) << endl;
  cout << add(a, c) << endl;
  cout << add(3.14159, 2.718281828) << endl;
  cout << add(b, 2.718281828) << endl;

  // Lambda expression used as a function pointer in the Algorithms
  // for-each statement.  Note the reference parameter when updating
  // the array object.
  int *A = new int[10];
  int sz = 10;
  for_each(A, A + sz, [](int &a) { a = rand() % 100; });
  for_each(A, A + sz, [](int a) { cout << a << " "; });
  cout << endl;

  // Same as above but allowing a capture of the variable n.
  int n = 1000;
  for_each(A, A + sz, [n](int &a) { a = rand() % n; });
  for_each(A, A + sz, [](int a) { cout << a << " "; });
  cout << endl;

  // Lambda function pointer to define < between two integers.
  sort(A, A + sz, [](int a, int b) -> bool { return a < b; });
  printArray(A, sz);

  // Generalization of the previous to allow any type as long as
  // the type supports <.
  sort(A, A + sz, [](auto a, auto b) { return a < b; });
  printArray(A, sz);

  // Lambda function pointer to define > between two integers.
  sort(A, A + sz, [](int a, int b) -> bool { return a > b; });
  printArray(A, sz);

  // Definition of Less and Greater using lambda functions.
  auto Less = [](auto a, auto b) { return a < b; };
  auto Greater = [](auto a, auto b) { return a > b; };

  // Use of Less and Greater in the sort.  Syntax is just like a function
  // pointer.
  sort(A, A + sz, Less);
  printArray(A, sz);

  sort(A, A + sz, Greater);
  printArray(A, sz);

  // Series of examples for upper and lower case.
  string str = "Examples of Function Pointers";
  cout << str << endl;

  // Lambda function that defines ::toupper.
  transform(str.begin(), str.end(), str.begin(),
            [](int a) -> int { return toupper(a); });
  cout << str << endl;

  // Lambda function that defines ::tolower.
  transform(str.begin(), str.end(), str.begin(),
            [](int a) -> int { return tolower(a); });
  cout << str << endl;

  // Creation of a toUpper function that takes the string
  // parameter by value.
  auto toUpper = [](string str) -> string {
    string s = str;
    transform(s.begin(), s.end(), s.begin(),
              [](int a) -> int { return toupper(a); });
    return s;
  };

  string t = toUpper(str);
  cout << str << endl;
  cout << t << endl;

  // Creation of a toLower function that takes the string
  // parameter by value.
  auto toLower = [](string str) -> string {
    string s = str;
    transform(s.begin(), s.end(), s.begin(),
              [](int a) -> int { return tolower(a); });
    return s;
  };

  t = toLower(t);
  cout << t << endl;

  delete[] A;

  return 0;
}

/*
Description: Templated print.
Parameters: i of template type.
Return: None
Notes: None
*/

template <class T> void print(T &i) { cout << i << " "; }

/*
Description: Templated array printer using the for_each statement
from the Algorithm library and function pointer to templated print.
Parameters: A array of template type.
sz int size of the array.
Return: None
Notes: None
*/

template <class T> void printArray(T A[], int sz) {
  for_each(A, A + sz, print<T>);
  cout << endl;
}

/*
Description: Templated vector printer using the for_each statement
from the Algorithm library and function pointer to templated print.
Parameters: A vector of template type.
Return: None
Notes: None
*/

template <class T> void printVector(vector<T> A) {
  for_each(A.begin(), A.end(), print<T>);
  cout << endl;
}
