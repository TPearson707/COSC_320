#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Heap.h"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(0));

    int numbernodes = 0;
    cout << "Enter number of integers to use: ";
    cin >> numbernodes;

    int *A = new int[numbernodes];
    int *B = new int[numbernodes];
    for (int i = 0; i < numbernodes; i++) {
        B[i] = rand() % 1000000000 + 1;
    }

    copy(B, B + numbernodes, A);

    high_resolution_clock::time_point t1, t2;
    duration<double> time_span;

    // Heap sort array.
    t1 = high_resolution_clock::now();
    Heap<int>::sort(A, numbernodes);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time to Heap Sort: " << time_span.count() << " seconds." << endl;

    copy(B, B + numbernodes, A);

    // Algorithm/Radix sort array.
    t1 = high_resolution_clock::now();
    sort(A, A + numbernodes);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time to Algorithm Sort: " << time_span.count() << " seconds."
         << endl;

    delete[] A;
    delete[] B;

    return 0;
}
