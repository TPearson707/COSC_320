#include <iostream>
/*
 * Created By: Thomas Pearson
 * Date of Creation: 04/15/2024
 * Date of Last Update: 04/17/2024
 * Description: Testing program to take the Average IPL for AVL and Red Black Trees for insertion and deletion cycles across verious different
 * tree size and integer size.
 */

#include <cstdlib>
#include <ctime>
#include <chrono>

#include "AVLTree.h"
#include "RBTree.h"

using namespace std;
using namespace chrono;

void avlCycle(AVLTree<int> &, int);
void rbCycle(RBTree<int> &, int);

int main() {
    AVLTree<int> avl;
    RBTree<int> rb;
    int n; // number of nodes to insert
    int m; // range of integers to insert
    int cycles; // number of insertion/deletion cycles
    srand(time(0));

    cout << "Enter the number of nodes to be inserted: ";
    cin >> n;

    cout << "Enter the range of integers to be inserted: ";
    cin >> m;

    cout << "Enter the number of insertion/deletion cycles: ";
    cin >> cycles;

    cout << endl;

    int testCount = 0;
    int testCountMax = 7;

    for (testCount; testCount < testCountMax; testCount++) {

        switch(testCount) {
            case 0:
                n = 1000000;
                m = 1000;
                cycles = 100000;
                break;
            case 1:
                n = 1000000;
                m = 1000000;
                cycles = 100000;
                break;
            case 2:
                n = 1000000;
                m = 10000000;
                cycles = 100000;
                break;
            case 3:
                n = 10000000;
                m = 1000000;
                cycles = 1000000;
                break;
            case 4:
                n = 10000000;
                m = 10000000;
                cycles = 1000000;
                break;
            case 5:
                n = 10000000;
                m = 15000000;
                cycles = 1000000;
                break;
            case 6:
                n = 10000000;
                m = 15000000;
                cycles = 10000000;
        }

        cout << "Testing For" << endl << "Size: " << n << endl << "Range: " <<  m << endl << "Cycles: " << cycles << endl << endl;
        auto start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                avl.insertNode(rand() % m + 1);
            }

        auto stop = high_resolution_clock::now();
        auto elapsed = duration_cast<microseconds>(stop - start);
        cout << "Time to insert numbers into AVL Tree: " << elapsed.count() / 1000000.0 << " seconds" << endl;

        start = high_resolution_clock::now();

            for (int i = 0; i < n; i++) {
                rb.insert(rand() % m + 1);
            }

        stop = high_resolution_clock::now();
        elapsed = duration_cast<microseconds>(stop - start);
        cout << "Time to insert numbers into Red Black Tree: " << elapsed.count() / 1000000.0 << " seconds" << endl;

        double IPLPreCycleAVL = avl.getIPL();
        double IPLPreCycleRB = rb.getIPL();

        cout << "Average IPL of AVL before cycles: " << IPLPreCycleAVL << endl;
        cout << "Average IPL of Red Black before cycles: " << IPLPreCycleRB << endl;

        start = high_resolution_clock::now();

            for (int i = 0; i < cycles; i++) {
                avlCycle(avl, m);
            }

        stop = high_resolution_clock::now();
        elapsed = duration_cast<microseconds>(stop - start);
        cout << "Time to complete insertion and deletion cycles for AVL Tree: " << elapsed.count() / 1000000.0 << " seconds" << endl;

        start = high_resolution_clock::now();

            for (int i = 0; i < cycles; i++) {
                rbCycle(rb, m);
            }

        stop = high_resolution_clock::now();
        elapsed = duration_cast<microseconds>(stop - start);
        cout << "Time to complete insertion and deletion cycles Red Black Tree: " << elapsed.count() / 1000000.0 << " seconds" << endl;

        double IPLPostCycleAVL = avl.getIPL();
        double IPLPostCycleRB = rb.getIPL();

        cout << "Average IPL for AVL post cycle: " << IPLPostCycleAVL << endl;
        cout << "Average IPL for Red Black post cycle: " << IPLPostCycleRB << endl;

        avl.kill();
        rb.kill();

        cout << endl;

    }

    return 0;
}

/*
 * Name: avlCycle
 * Return Type: void
 * Parameters: AVLTree<int> & avl, int m
 * Description: Inserts a random integer in range m into the tree then randomly selects a number until it finds one in tree then deletes it
 */
void avlCycle(AVLTree<int> & avl, int m) {
    avl.insertNode(rand() % m + 1);

    bool deletion = false;
    int num;

    while (!deletion) {
        num = rand() % m + 1;
        if (avl.searchNode(num)) {
            avl.remove(num);
            deletion = true;
        }
    }

}

/*
 * Name: RBCycle
 * Return Type: void
 * Parameters: RBTree<int> & rb, int m
 * Description: Inserts a random integer in range m into the tree then randomly selects a number until it finds one in tree then deletes it
 */
void rbCycle(RBTree<int> & rb, int m) {
    rb.insert(rand() % m + 1);

    bool deletion = false;
    int num;

    while (!deletion) {
        num = rand() % m + 1;

        if (rb.find(num)) {
            rb.remove(num);
            deletion = true;
        }
    }
}
