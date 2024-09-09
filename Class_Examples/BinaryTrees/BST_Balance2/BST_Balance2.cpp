#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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
	int num;

	cout << "Input the number of nodes: ";
	cin >> num;

	for (int i = 0; i < num; i++)
		tree.insertNode(rand() % 100);

	tree.PrintTree();

	cout << "Height = " << tree.height() << endl;
	line(1);

	tree.balance();
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	line(2);

	cout << "Input node to remove: ";
	cin >> num;

	tree.remove(num);
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	line(3);

	tree.balance();
	tree.PrintTree();
	cout << "Height = " << tree.height() << endl;

	line(4);

	tree.clear();
	for (int i = 0; i < 1000000; i++)
		tree.insertNode(rand() % 1000000);

	cout << "Height = " << tree.height() << endl;
	tree.balance();
	cout << "Height = " << tree.height() << endl;

	return 0;
}
