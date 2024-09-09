#include <iostream>
#include <cstdlib>
#include <ctime>

#include "BinaryTree.h"

using namespace std;

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

	tree.insertNode(5);
	tree.insertNode(11);
	tree.insertNode(3);
	tree.insertNode(2);
	tree.insertNode(7);
	tree.insertNode(8);
	tree.insertNode(10);
	tree.insertNode(6);

	// Display the values, recursively.
	cout << "Here are the values in the tree:\n";
	tree.displayInOrder();

	line(1);

	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(2);

	cout << "Delete by copy, value 7\n";
	tree.deleteValue(7);
	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(3);

	cout << "Insert, values 7, 8, 9, 10, 11, 12. \n";
	tree.insertNode(7);
	tree.insertNode(8);
	tree.insertNode(9);
	tree.insertNode(10);
	tree.insertNode(11);
	tree.insertNode(12);

	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(4);

	cout << "Delete by copy, value 8\n";
	tree.deleteValue(8);
	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(5);

	cout << "Delete by copy, value 10\n";
	tree.deleteValue(10);
	cout << "\nTree:\n";
	tree.PrintTree(4);

	line(6);

	cout << "Delete by copy, value 10\n";
	tree.deleteValue(10);
	cout << "\nTree:\n";
	tree.PrintTree(4);

	return 0;
}
