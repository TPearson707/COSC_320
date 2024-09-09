// Author: Erich Vonderhorst
// Creation Date: 3/15/2023
// Last Update: 3/15/2023
// Description: timing program for several runs of different sorting algorithm functions with different
//              array sizes, value ranges, and radices.

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Sorts.h"

using namespace std;
using namespace std::chrono;

int main() {
    ofstream outFile;
    outFile.open("results.csv");

    outFile << "sort/size,merge,quick,comb,shell,heap,alglib,radix10nmax,radix100rmax,radix1000rmax,radix10000rmax,"
          << "radix10n1000,radix100n1000,radix1000n1000,radix10000n1000,countrmax,countn1000,bucket" << endl;

    int sizes[] = {1000, 5000, 10000, 25000, 50000, 100000, 500000, 1000000, 5000000, 10000000};

    int *iArr;
    double* dArr;
    srand(time(0));

    for (int i = 0; i < 10; i++) {
      outFile << sizes[i] << ",";
      iArr = new int[sizes[i]];
      dArr = new double[sizes[i]];

      for (int j = 0; j < sizes[i]; j++) {
        iArr[j] = rand();
        cout << iArr[i] << endl;
      }
      auto start = high_resolution_clock::now();
      mergeSort(iArr, sizes[i]);
      auto stop = high_resolution_clock::now();
      auto elapsed = duration_cast<microseconds>(stop - start);
      outFile << elapsed.count() / 1000000.0 << ",";





      outFile << endl;
      delete[] iArr;
      delete[] dArr;

    }

    return 0;
}
