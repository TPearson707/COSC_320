/*
Author: Don Spickler
Creation Date: 1/25/2024
Last Update: 1/25/2024
Description:  Example of how to time a process in C++ using a
timer macro based on the gettimeofday command in time.h.
User Interface: None
Notes: None
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "timer.h"

using namespace std;

int main() {

  double start, finish, elapsed;

  // Define and populate a vector of random values.
  srand(time(0));
  vector<int> values(10000000);

  for (unsigned int i = 0; i < values.size(); i++)
    values[i] = rand();

  // Get start time.
  GET_TIME(start);

  // Do process to be timed.
  sort(values.begin(), values.end());

  // Get stop time.
  GET_TIME(finish);

  // Report time.
  elapsed = finish - start;
  cout << "Time to sort: " << elapsed << " seconds" << endl;

  // Reuse
  GET_TIME(start);
  sort(values.begin(), values.end());
  GET_TIME(finish);
  elapsed = finish - start;
  cout << "Time to sort: " << elapsed << " seconds" << endl;

  return 0;
}
