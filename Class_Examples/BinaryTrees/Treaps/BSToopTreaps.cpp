#include <iostream>

//#include "AVLTree.h"
#include "Treap.h"

using namespace std;

int main() {
	srand(time(0));

	// Create the binary tree.
	Treap<int> tree;
	int numbernodes = 0;
	int printTrees = 1;

	cout << "Enter number of nodes to insert: ";
	cin >> numbernodes;

	cout << "Print Trees (Yes = 1, No = 0): ";
	cin >> printTrees;

	// Insert.
	if (printTrees)
		cout << "Insertion order: ";
	else
		cout << "Inserting: ";

	for (int i = 0; i < numbernodes; i++) {
		int val = rand() % 100 + 1;
		tree.insert(val);
		if (printTrees)
			cout << val << " ";
	}

	if (printTrees) {
		cout << endl;
		cout << "\nTree:\n";
		tree.PrintTree();
		cout << endl << endl;
		tree.PrintTreeP();
	}

	cout << "Enter number of nodes to remove: ";
	cin >> numbernodes;

	int count = 0;
	while (count < numbernodes) {
		int val = rand() % 100 + 1;
		if (tree.find(val)) {
			tree.remove(val);
			count++;
		}
	}

	cout << endl << endl;
	tree.PrintTreeP();

	return 0;
}
