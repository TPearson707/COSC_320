#include <iostream>
#include <cstdlib>
#include <ctime>

#include "BinaryTree.h"

using namespace std;

const int NUM_NODES = 10;

void line(int n = 0) {
	if (n > 0)
		cout << "\n" << n << " ---------------------------------------\n\n";
	else
		cout << "\n---------------------------------------\n\n";
}

int main() {
	srand(time(0));

	// Create the binary tree.
	BinaryTree<int> tree;

	for (int count = 0; count < NUM_NODES; count++) {
		tree.insertNode(rand() % 100);
	}

	// Display the values, recursively.
	cout << "\nHere are the values in the tree:\n";
	tree.displayInOrder();

	line(1);

	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(2);

	tree.displayBreadthFirst();

	line(3);

	tree.displayPreOrder();
	line();
	tree.iterativePreorder();

	line(4);

	tree.displayPreOrder();
	line();
	tree.iterativePreorder();

	line(5);

	tree.displayPostOrder();
	line();
	tree.iterativePostorder2Stacks();
	line();
	tree.iterativePostorder();

	line(6);

	tree.displayInOrder();
	line();
	tree.iterativeInorder();

	return 0;
}
