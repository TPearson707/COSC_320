#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Heap.h"

using namespace std;

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

    while (!H.empty()){
        cout << H.dequeue() << " ";
    }
    cout << endl;

    return 0;
}
