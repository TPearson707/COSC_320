#include <iostream>

#include "AVLTree.h"

using namespace std;

int main() {
	srand(time(0));

	// Create the binary tree.
	AVLTree<int> tree;
	int numbernodes = 0;
	int printTrees = 0;

	cout << "Enter number of nodes to insert: ";
	cin >> numbernodes;

	cout << "Print Trees (Yes = 1, No = 0): ";
	cin >> printTrees;

	// Insert.
	if (printTrees)
		cout << "Insertion order: ";
	else
		cout << "Inserting: ";

	//*
	for (int i = 0; i < numbernodes; i++) {
		int val = rand() % 100 + 1;
		tree.insert(val);
		if (printTrees)
			cout << val << " ";
	}
	// */

	/*
	 for (int i = 0; i < numbernodes; i++) {
	 int val = i;
	 tree.insertNode(val);
	 if (printTrees)
	 cout << val << " ";
	 }
	 // */

	if (printTrees) {
		cout << endl;
		cout << "\nTree:\n";
		tree.PrintTree();

		cout << endl;
		cout << "\nTree with height and balance values:\n";
		tree.PrintTreeHB();
	}

	cout << endl;
	if (tree.isBalanced())
		cout << "Tree is balanced." << endl;
	else
		cout << "Tree is NOT balanced." << endl;

	cout << tree.find(35) << endl;
	cout << tree.find(21) << endl;
	cout << tree.find(52) << endl;
	cout << tree.find(123) << endl;

	return 0;
}
