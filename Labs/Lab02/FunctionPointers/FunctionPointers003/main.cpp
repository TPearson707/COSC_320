/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Example of using a function pointer array to alter the called
function.
*/

#include <iostream>

using namespace std;

/*
Description: Simple arithmetic operations to illustrate the call.
Parameters: x, y, type T.
Return: Type T result of the arithmetic operation.
*/

template <class T> T add(T x, T y) { return x + y; }
template <class T> T sub(T x, T y) { return x - y; }
template <class T> T mul(T x, T y) { return x * y; }
template <class T> T div(T x, T y) { return x / y; }

int main() {
  // An array of pointers to functions with two double parameters and double
  // return type.
  double (*fctptr[4])(double, double) = {add, sub, mul, div};

  for (int i = 0; i < 4; i++)
    cout << fctptr[i](3, 7) << endl;

  return 0;
}
