#ifndef BST_H_
#define BST_H_

#include <cmath>

#include "BinaryTree.h"

template<class T>
class BST: public BinaryTree<T> {
protected:
	void insert(TreeNode<T>*&, TreeNode<T>*&);
	void deleteNode(T, TreeNode<T>*&);
	void makeDeletion(TreeNode<T>*&);

public:
	BST();
	virtual ~BST();

	void insert(T);
	void remove(T);

	virtual bool find(const T&);
	virtual TreeNode<T>* findNode(const T&);

	void balance();
	void CreateBackbone();
	int CountNodesLL();
	void RightRotation(TreeNode<T> *&nodePtr);
	void LeftRotation(TreeNode<T> *&nodePtr);
	void CreateBalance(int num);
};

template<class T>
BST<T>::BST() {
}

template<class T>
BST<T>::~BST() {
}

template<class T>
void BST<T>::insert(TreeNode<T> *&nodePtr, TreeNode<T> *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode;
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode);
	else
		insert(nodePtr->right, newNode);
}

template<class T>
void BST<T>::insert(T item) {
	TreeNode<T> *newNode = new TreeNode<T>;
	newNode->value = item;
	insert(BinaryTree<T>::root, newNode);
}

template<class T>
bool BST<T>::find(const T &item) {
	return findNode(item) != nullptr;
}

template<class T>
TreeNode<T>* BST<T>::findNode(const T &item) {
	TreeNode<T> *nodePtr = BinaryTree<T>::root;

	while (nodePtr) {
		if (nodePtr->value == item)
			return nodePtr;
		else if (item < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return nullptr;
}

template<class T> void BST<T>::remove(T item) {
	deleteNode(item, BinaryTree<T>::root);
}

template<class T> void BST<T>::deleteNode(T item, TreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else
		makeDeletion(nodePtr);
}

template<class T> void BST<T>::makeDeletion(TreeNode<T> *&nodePtr) {
	TreeNode<T> *tempNodePtr = nullptr;

	if (!nodePtr)
		cout << "Cannot delete empty node.\n";
	else if (!nodePtr->right) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;
	} else if (!nodePtr->left) {
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	} else {
		tempNodePtr = nodePtr->right;
		while (tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;
	}
}

/*
 * Does a right rotation about nodePtr.
 */
template<class T> void BST<T>::RightRotation(TreeNode<T> *&nodePtr) {
	TreeNode<T> *L = nodePtr->left;
	TreeNode<T> *temp = L->right;
	L->right = nodePtr;
	nodePtr->left = temp;
	nodePtr = L;
}

/*
 * Does a left rotation about nodePtr.
 */
template<class T> void BST<T>::LeftRotation(TreeNode<T> *&nodePtr) {
	TreeNode<T> *R = nodePtr->right;
	TreeNode<T> *temp = R->left;
	R->left = nodePtr;
	nodePtr->right = temp;
	nodePtr = R;
}

/*
 * Counts the number of nodes in a binary tree starting at the root.
 * Assumes that the tree is a degenerate linked list with only right
 * children, that is, a backbone.
 */
template<class T> int BST<T>::CountNodesLL() {
	TreeNode<T> *ptr = this->root;
	if (!this->root)
		return 0;

	int count = 0;
	while (ptr) {
		count++;
		ptr = ptr->right;
	}

	return count;
}

/*
 * Iterative version of a single pass in tree balancing using DSW.
 */
template<class T> void BST<T>::CreateBalance(int num) {
	if (num == 0)
		return;

	LeftRotation(this->root);
	TreeNode<T> *ptr = this->root;
	for (int i = 0; i < num - 1; i++) {
		LeftRotation(ptr->right);
		ptr = ptr->right;
	}
}

/*
 * DSW (Colin Day, Quentin F. Stout, and Bette L. Warren) tree balancing algorithm
 * the first creates a backbone of the tree, then using left rotations forms a
 * perfectly balanced tree.
 */
template<class T> void BST<T>::balance() {
	if (!this->root)
		return;

	CreateBackbone();
	int n = CountNodesLL();

	// The addition of 0.5 is a standard rounding procedure when truncating to
	// an integer.  In the case of 1.9999999 when the true result is 2.
	int m = static_cast<int>(pow(2, floor(log2(n + 1))) - 1 + 0.5);

	CreateBalance(n - m);
	while (m > 1) {
		m = m / 2;
		CreateBalance(m);
	}
}

/*
 * Iterative version that reforms the tree into a "backbone".  That is, a
 * linked list to the right child where the values will be ordered.
 */
template<class T> void BST<T>::CreateBackbone() {
	if (!this->root)
		return;

	while (this->root->left) {
		RightRotation(this->root);
	}

	TreeNode<T> *ptr = this->root;
	while (ptr->right) {
		while (ptr->right->left) {
			RightRotation(ptr->right);
		}
		ptr = ptr->right;
	}
}

#endif /* BST_H_ */
