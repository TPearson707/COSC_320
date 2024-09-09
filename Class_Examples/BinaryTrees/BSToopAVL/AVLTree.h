#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "BinaryTree.h"

using namespace std;

template<class T>
class AVLTreeNode {
public:
	T value;
	int height = 1;  //  Height of the subtree below the node.
	AVLTreeNode *left;
	AVLTreeNode *right;

	AVLTreeNode() {
		left = nullptr;
		right = nullptr;
	}
};

template<class T> class AVLTree: public BinaryTree<T, AVLTreeNode<T>> {
protected:

	void insert(AVLTreeNode<T>*&, AVLTreeNode<T>*&);
	void deleteNode(T, AVLTreeNode<T>*&);

	void LeftRotation(AVLTreeNode<T>*&);
	void RightRotation(AVLTreeNode<T>*&);
	int getBalanceFactor(AVLTreeNode<T>*);
	int getHeight(AVLTreeNode<T>*);
	void Balance(AVLTreeNode<T>*&);

	// Testing Functions
	bool isBalanced(AVLTreeNode<T>*);
	void IndentBlock(int);
	void PrintTreeHB(AVLTreeNode<T>*, int, int);

public:
	AVLTree() {
	}
	~AVLTree() {
	}

	void insert(T);
	void remove(T);

	virtual bool find(const T&);
	virtual AVLTreeNode<T>* findNode(const T&);

	// Testing Functions
	bool isBalanced();
	void PrintTreeHB(int Indent = 4, int Level = 0);
};

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T> void AVLTree<T>::RightRotation(AVLTreeNode<T> *&nodePtr) {
	AVLTreeNode<T> *L = nodePtr->left;
	AVLTreeNode<T> *temp = L->right;
	L->right = nodePtr;
	nodePtr->left = temp;
	nodePtr->height = max(getHeight(nodePtr->left), getHeight(nodePtr->right))
			+ 1;
	L->height = max(getHeight(L->left), getHeight(L->right)) + 1;
	nodePtr = L;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T> void AVLTree<T>::LeftRotation(AVLTreeNode<T> *&nodePtr) {
	AVLTreeNode<T> *R = nodePtr->right;
	AVLTreeNode<T> *temp = R->left;
	R->left = nodePtr;
	nodePtr->right = temp;
	nodePtr->height = max(getHeight(nodePtr->left), getHeight(nodePtr->right))
			+ 1;
	R->height = max(getHeight(R->left), getHeight(R->right)) + 1;
	nodePtr = R;
}

/*
 Returns the height of the subtree pointed to by nodePtr.

 Parameters
 nodePtr --- pointer to the node.
 */
template<class T> int AVLTree<T>::getHeight(AVLTreeNode<T> *nodePtr) {
	if (!nodePtr)
		return 0;

	return nodePtr->height;
}

/*
 Returns the balance factor of the node pointed to by nodePtr.

 Parameters
 nodePtr --- pointer to the node.
 */
template<class T> int AVLTree<T>::getBalanceFactor(AVLTreeNode<T> *nodePtr) {
	if (!nodePtr)
		return 0;

	return getHeight(nodePtr->left) - getHeight(nodePtr->right);
}

/*
 Does one balance of the subtree at the given node.

 Parameters
 nodePtr --- pointer to the node.
 */
template<class T> void AVLTree<T>::Balance(AVLTreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	// Rebalance if needed.
	int balanceFactor = getBalanceFactor(nodePtr);

	// Rebalance if needed.
	// Left heavy.
	if (balanceFactor > 1) {
		if (getBalanceFactor(nodePtr->left) > 0)
			RightRotation(nodePtr);
		else {
			LeftRotation(nodePtr->left);
			RightRotation(nodePtr);
		}
	}

	// Right heavy.
	if (balanceFactor < -1) {
		if (getBalanceFactor(nodePtr->right) > 0) {
			RightRotation(nodePtr->right);
			LeftRotation(nodePtr);
		} else
			LeftRotation(nodePtr);
	}
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template<class T>
void AVLTree<T>::insert(AVLTreeNode<T> *&nodePtr, AVLTreeNode<T> *&newNode) {
	if (nodePtr == nullptr)
		nodePtr = newNode; // Insert the node.
	else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch

	// Update the height of each node in the branches called.
	nodePtr->height = 1
			+ max(getHeight(nodePtr->left), getHeight(nodePtr->right));

	Balance(nodePtr);
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template<class T> void AVLTree<T>::insert(T item) {
	AVLTreeNode<T> *newNode = nullptr; // Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new AVLTreeNode<T>;
	newNode->value = item;
	newNode->left = newNode->right = nullptr;

	// Insert the node.
	insert(this->root, newNode);
}

/*
 * Finds if item is in the tree. Returns true if the item is in
 * the tree and false otherwise.
 */
template<class T>
bool AVLTree<T>::find(const T &item) {
	return findNode(item) != nullptr;
}

/*
 * Finds if item is in the tree. Returns a pointer to the node if it is in the
 * tree and null if not.
 */
template<class T>
AVLTreeNode<T>* AVLTree<T>::findNode(const T &item) {
	AVLTreeNode<T> *nodePtr = this->root;

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

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template<class T> void AVLTree<T>::remove(T item) {
	deleteNode(item, this->root);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template<class T> void AVLTree<T>::deleteNode(T item,
		AVLTreeNode<T> *&nodePtr) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNode(item, nodePtr->left);
	else if (item > nodePtr->value)
		deleteNode(item, nodePtr->right);
	else {
		if (!nodePtr->left || !nodePtr->right) {
			AVLTreeNode<T> *tempNodePtr = nullptr;
			if (!nodePtr->left)
				tempNodePtr = nodePtr->right;
			else
				tempNodePtr = nodePtr->left;

			if (!tempNodePtr) {
				tempNodePtr = nodePtr;
				nodePtr = nullptr;
			} else
				*nodePtr = *tempNodePtr;
			delete tempNodePtr;
		} else {
			AVLTreeNode<T> *tempNodePtr = nodePtr->right;
			// Go to the end left node.
			while (tempNodePtr->left)
				tempNodePtr = tempNodePtr->left;
			nodePtr->value = tempNodePtr->value;
			deleteNode(tempNodePtr->value, nodePtr->right);
		}
	}

	if (!nodePtr)
		return;

	// Update the height of each node in the branches called.
	nodePtr->height = 1
			+ max(getHeight(nodePtr->left), getHeight(nodePtr->right));

	int balanceFactor = getBalanceFactor(nodePtr);
	while (balanceFactor > 1 || balanceFactor < -1) {
		Balance(nodePtr);
		balanceFactor = getBalanceFactor(nodePtr);
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T> void AVLTree<T>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template<class T>
void AVLTree<T>::PrintTreeHB(AVLTreeNode<T> *t, int Indent, int Level) {
	if (t) {
		int bal = getBalanceFactor(t);
		PrintTreeHB(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "/" << t->height << "/" << bal << "\n";
		PrintTreeHB(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template<class T> void AVLTree<T>::PrintTreeHB(int Indent, int Level) {
	if (this->root)
		PrintTreeHB(this->root, Indent, Level);
}

//****************************************************************
// This function is a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template<class T> bool AVLTree<T>::isBalanced(AVLTreeNode<T> *t) {
	if (!t)
		return true;

	if (getBalanceFactor(t) > 1 || getBalanceFactor(t) < -1)
		return false;
	else
		return isBalanced(t->left) && isBalanced(t->right);
}

//****************************************************************
// This function initiates a recursive function to test if the AVL
// Tree is balanced.
//****************************************************************

template<class T> bool AVLTree<T>::isBalanced() {
	if (this->root)
		return isBalanced(this->root);

	return true;
}

#endif
