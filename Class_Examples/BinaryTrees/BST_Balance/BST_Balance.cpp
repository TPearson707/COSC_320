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
	BinaryTree<int> tree;

	tree.insertNode(5);
	tree.insertNode(9);
	tree.insertNode(2);
	tree.insertNode(3);
	tree.insertNode(6);
	tree.insertNode(1);
	tree.insertNode(7);
	tree.insertNode(3);
	tree.insertNode(8);
	tree.insertNode(5);
	tree.insertNode(10);
	tree.insertNode(13);
	tree.insertNode(11);
	tree.insertNode(4);
	tree.insertNode(12);
	tree.insertNode(7);

	tree.PrintTree();

	cout << "Height = " << tree.height() << endl;
	line(1);

	tree.balance();
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	line(2);

	tree.remove(4);
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	line(3);

	tree.balance();
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	tree.clear();

	line(4);

	for (int i = 0; i < 100000; i++)
		tree.insertNode(rand() % 1000000);

	cout << "Height = " << tree.height() << endl;
	tree.balance();
	cout << "Height = " << tree.height() << endl;

	return 0;
}
