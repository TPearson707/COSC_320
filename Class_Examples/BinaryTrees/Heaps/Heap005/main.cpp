#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Heap.h"

using namespace std;

int main() {
    srand(time(0));
    int size = 40;
    int A[size];

    for (int i = 0; i < size; i++)
    	A[i] = rand() % 100 + 1;

    for (int i = 0; i < size; i++)
    	cout << A[i] << " ";
    cout << endl;

    Heap<int> H(A, size);
    cout << H << endl;

    return 0;
}
