#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Heap.h"

using namespace std;

// Priority Queue node taken from previous assignments. Added < and <<.
template <class T> class PQNode {
  public:
    T data;
    int priority;

    PQNode(T Data) {
        data = Data;
        priority = 1;
    }

    PQNode(T Data, int Priority) {
        data = Data;
        if (Priority < 1)
            Priority = 1;

        priority = Priority;
    }

    bool operator<(const PQNode<T> &obj) { return priority < obj.priority; }

    friend ostream &operator<<(ostream &strm, const PQNode<T> &obj) {
        strm << "<" << obj.priority << ", " << obj.data << ">";
        return strm;
    }
};

int main() {
    srand(time(0));
    Heap<PQNode<string>> H;

    H.insert(PQNode<string>("This is important.", 4));
    H.insert(PQNode<string>("This is also important.", 4));
    H.insert(PQNode<string>("This is not as important.", 3));
    H.insert(PQNode<string>("Got to do this now!", 6));
    H.insert(PQNode<string>("This is not important.", 2));
    H.insert(PQNode<string>("This is not important at all.", 1));
    H.insert(PQNode<string>("This is again important.", 4));
    H.insert(PQNode<string>("This is really important.", 5));
    H.insert(PQNode<string>("This is more important.", 6));
    H.insert(PQNode<string>("Don't bother.", 1));

    cout << H << endl;
    cout << endl;

    while (!H.empty()) {
        cout << H.dequeue() << "\n";
    }
    cout << endl;

    return 0;
}
