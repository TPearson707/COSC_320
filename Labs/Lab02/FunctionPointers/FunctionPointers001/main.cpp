/*
Author: Don Spickler
Creation Date: 1/10/2022
Last Update: 1/22/2024
Description: Example of using function pointers to alter the called function.
*/

#include <iostream>

using namespace std;

/*
Description: Simple arithmetic operations to illustrate the call.
Parameters: x, y, doubles.
Return: double result of the arithmetic operation.
*/

double add(double x, double y) { return x + y; }
double sub(double x, double y) { return x - y; }
double mul(double x, double y) { return x * y; }
double div(double x, double y) { return x / y; }

int main() {
  // Pointer to a function with two double parameters and double return type.
  double (*fctptr)(double, double);

  fctptr = add;
  cout << fctptr(3, 7) << endl;
  fctptr = sub;
  cout << fctptr(3, 7) << endl;
  fctptr = mul;
  cout << fctptr(3, 7) << endl;
  fctptr = div;
  cout << fctptr(3, 7) << endl;

  return 0;
}
