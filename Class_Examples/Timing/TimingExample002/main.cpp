/*
Author: Don Spickler
Creation Date: 1/25/2024
Last Update: 1/25/2024
Description:  Example of how to time a process in C++ using the chrono
library. Difference here is the use of explicit typing in place of the auto
type.  Also getting time on a nanosecond scale.
User Interface: None
Notes: None
*/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;

int main() {
  // Define and populate a vector of random values.
  srand(time(0));
  vector<int> values(10000000);

  for (unsigned int i = 0; i < values.size(); i++)
    values[i] = rand();

  // Get start time.
  high_resolution_clock::time_point start = high_resolution_clock::now();

  // Do process to be timed.
  sort(values.begin(), values.end());

  // Get stop time.
  high_resolution_clock::time_point stop = high_resolution_clock::now();

  // Take the difference to get elapsed time.
  high_resolution_clock::duration elapsed =
      duration_cast<nanoseconds>(stop - start);

  // Report time.
  cout << "Time to sort: " << elapsed.count() << " nanoseconds" << endl;
  cout << "Time to sort: " << elapsed.count() / 1000000000.0 << " seconds"
       << endl;

  // Reuse of variables.
  start = high_resolution_clock::now();
  sort(values.begin(), values.end());
  stop = high_resolution_clock::now();
  elapsed = duration_cast<nanoseconds>(stop - start);

  cout << "Time to sort: " << elapsed.count() << " nanoseconds" << endl;
  cout << "Time to sort: " << elapsed.count() / 1000000000.0 << " seconds"
       << endl;

  return 0;
}
