#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RBTree.h"

using namespace std;

int main() {
	srand(time(0));
	RBTree<int> RBT;

	int num;
	cout << "Number of nodes to insert: ";
	cin >> num;

	for (int i = 0; i < num; i++)
		RBT.insert(rand() % 100);

	RBT.PrintTree();

	cout << "\n--------------------------------\n\n";

	cout << "Item to delete: ";
	cin >> num;

	RBT.remove(num);
	cout << endl;

	RBT.PrintTree();

	cout << "\n--------------------------------\n\n";

	return 0;
}
