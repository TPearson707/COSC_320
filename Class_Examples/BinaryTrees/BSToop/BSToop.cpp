#include <iostream>

#include "BinaryTree.h"
#include "BST.h"

using namespace std;

void line(int n = 0) {
	if (n > 0)
		cout << "\n" << n << " ---------------------------------------\n\n";
	else
		cout << "\n---------------------------------------\n\n";
}

template<class T>
void print(T &item) {
	cout << item << " ";
}

template<class T>
void twice(T &item) {
	item *= 2;
}

int main() {
	BST<int> tree;

	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(3);
	tree.insert(6);

	tree.InOrder(print);
	cout << endl;
	tree.InOrder(twice);
	tree.InOrder(print);
	cout << endl;
	tree.PreOrder(print);
	cout << endl;
	tree.PostOrder(print);
	cout << "\n\n";

	line(1);

	tree.PrintTree();

	line(2);

	cout << tree.find(18) << endl;
	cout << tree.find(19) << endl;
	cout << tree.findNode(18) << endl;
	cout << tree.findNode(19) << endl;
	cout << "\n";

	tree.insert(5);
	tree.insert(9);
	tree.insert(2);
	tree.insert(3);
	tree.insert(6);

	line(3);

	tree.PrintTree();

	line(4);

	tree.remove(4);

	tree.PrintTree();

	return 0;
}
