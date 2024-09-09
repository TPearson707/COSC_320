/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 03/09/2024
 * Date of Last Update: 03/09/2024
 * Description: Testing program for IntBinaryTree class
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "IntBinaryTree.h"

using namespace std;
using namespace chrono;

int main() {
	srand(time(0));
	int size;
	int* arr;
	cout << "Enter a size for the array: ";
	cin >> size;
	cout << endl;

	arr = new int[size]();

	for (int i = 0; i < size; i++)
		arr[i] = rand() % 1000000 + 1;

	IntBinaryTree tree;

	// Get start time.
    auto start = high_resolution_clock::now();

    // Do process to be timed.
	tree.loadArray(arr, size);
    tree.fillArray(arr, size);

    // Get stop time.
    auto stop = high_resolution_clock::now();

    // Take the difference t get elapsed time.
    auto elapsed = duration_cast<microseconds>(stop - start);

    // Report time.
    cout << "Time to sort using treeSort : " << elapsed.count() / 1000000.0 << " seconds" << endl;

	delete[] arr;
	return 0;
}
