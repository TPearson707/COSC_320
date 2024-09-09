#include <iostream>
#include "BinaryTree.h"

using namespace std;

const int NUM_NODES = 5;

int main() {
	int item;

	// Create the binary tree.
	BinaryTree<int> tree;

	// Insert some names.
	for (int count = 0; count < NUM_NODES; count++) {
		cout << "Enter a number: ";
		cin >> item;
		tree.insertNode(item);
	}

	// Display the values.
	cout << "\nHere are the values in the tree:\n";
	tree.displayInOrder();

	cout << "\nTree:\n";
	tree.PrintTree(4);

	cout << "Enter a number to search for: ";
	cin >> item;
	int *result = tree.search(item);

	if (result)
		cout << *result << " was found at " << result << "." << endl;
	else
		cout << item << " was not found.";

	return 0;
}
