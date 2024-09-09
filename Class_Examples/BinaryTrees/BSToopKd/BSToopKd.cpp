#include <iostream>
#include <vector>

#include "Kd.h"

using namespace std;

int main() {
	srand(time(0));

	// Create the binary tree.
	KdTree<vector<int>> tree;
	int numbernodes = 0;
	int datanum = 0;
	int printTrees = 1;

	cout << "Enter number of nodes to insert: ";
	cin >> numbernodes;

	cout << "Enter number of data items per node: ";
	cin >> datanum;

	cout << "Print Trees (Yes = 1, No = 0): ";
	cin >> printTrees;

	vector<int> nodeitem;
	for (int i = 0; i < numbernodes; i++) {
		nodeitem.clear();
		for (int j = 0; j < datanum; j++) {
			nodeitem.push_back(rand() % 100);
		}
		tree.insert(nodeitem);
	}

	if (printTrees) {
		cout << endl;
		cout << "\nTree:\n";
		tree.PrintTreeList();
		cout << endl;
	}

	if (tree.isKd())
		cout << "Tree is a K-d tree." << endl;
	else
		cout << "Tree is not a K-d tree." << endl;
	cout << endl;

	int val = 0;

	cout << "Enter item to find: ";
	nodeitem.clear();
	for (int j = 0; j < datanum; j++) {
		cin >> val;
		nodeitem.push_back(val);
	}

	if (tree.find(nodeitem))
		cout << "Item was found." << endl;
	else
		cout << "Item was not found." << endl;
	cout << endl;

	cout << "Enter item to delete: ";
	val = 0;
	nodeitem.clear();
	for (int j = 0; j < datanum; j++) {
		cin >> val;
		nodeitem.push_back(val);
	}

	tree.remove(nodeitem);

	if (printTrees) {
		cout << endl;
		cout << "\nTree:\n";
		tree.PrintTreeList();
		cout << endl;
	}

	if (tree.isKd())
		cout << "Tree is a K-d tree." << endl;
	else
		cout << "Tree is not a K-d tree." << endl;
	cout << endl;

	return 0;
}
