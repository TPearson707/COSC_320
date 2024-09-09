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
Parameters: x, y, doubles.
Return: double result of the arithmetic operation.
*/

double add(double x, double y) { return x + y; }
double sub(double x, double y) { return x - y; }
double mul(double x, double y) { return x * y; }
double div(double x, double y) { return x / y; }

int main() {
  // An array of pointers to functions with two double parameters and double
  // return type.
  double (*fctptr[4])(double, double);

  fctptr[0] = add;
  fctptr[1] = sub;
  fctptr[2] = mul;
  fctptr[3] = div;

  for (int i = 0; i < 4; i++)
    cout << fctptr[i](3, 7) << endl;

  return 0;
}
