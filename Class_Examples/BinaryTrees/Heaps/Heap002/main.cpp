#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Heap.h"

using namespace std;

void div() { cout << "\n----------------------\n\n"; }

template <class T> void dequeueAll(Heap<T> &H) {
    while (!H.empty()) {
        cout << H.dequeue() << " ";
    }
    cout << endl;
}

template <class T> void PrintVector(vector<T> v) {
    for (T item : v) {
        cout << item << " ";
    }
    cout << endl;
}

template <class T> void PrintArray(T A[], int s) {
    for (int i = 0; i < s; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    Heap<int> H;

    for (int i = 0; i < 15; i++)
        H.insert(rand() % 100 + 1);

    cout << H << endl;

    cout << H.dequeue() << endl;
    cout << H << endl;
    cout << H.dequeue() << endl;
    cout << H << endl;
    cout << endl;

    dequeueAll(H);

    H.clear();

    div();

    vector<int> v = {3, 6, 5, 9, 2, 1, 5};
    Heap<int> H2(v);
    cout << H2 << endl;
    dequeueAll(H2);

    int A[] = {3, 6, 5, 9, 2, 1, 5, 6, 2, 3, 7, 5};
    Heap<int> H3(A, 12);
    cout << H3 << endl;
    dequeueAll(H3);

    H2.setData(v);
    cout << H2 << endl;
    dequeueAll(H2);

    H2.setData(A, 12);
    cout << H2 << endl;
    dequeueAll(H2);

    div();

    H2.setData(v);
    cout << H2 << endl;
    H2.append(v);
    cout << H2 << endl;
    dequeueAll(H2);

    div();

    H2.setData(v);
    cout << H2 << endl;
    H2.append(A, 12);
    cout << H2 << endl;
    dequeueAll(H2);

    div();

    Heap<int>::sort(v);
    PrintVector(v);

    Heap<int>::sort(A, 12);
    PrintArray(A, 12);

    return 0;
}
