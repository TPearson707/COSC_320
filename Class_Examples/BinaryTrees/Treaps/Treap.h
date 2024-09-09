#ifndef TREAP_H_
#define TREAP_H_

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "BST.h"

using namespace std;

template<class T>
class TreapNode {
public:
	T value;
	int priority = 0;
	TreapNode *left;
	TreapNode *right;

	TreapNode() {
		left = nullptr;
		right = nullptr;
	}
};

template<class T, class Node = TreapNode<T>>
class Treap: public BST<T, Node> {
protected:
	void LeftRotation(Node*&);
	void RightRotation(Node*&);
	void insert(Node*&, Node*&);
	void deleteNodeFind(T, Node*&, Node*&);
	void deleteNode(Node*&, Node*&);
	void IndentBlock(int);
	void PrintTreeP(Node*, int, int);

public:
	Treap();
	virtual ~Treap();

	void insert(T);
	void remove(T);

	void PrintTreeP(int Indent = 4, int Level = 0);
};

template<class T, class Node>
Treap<T, Node>::Treap() {
}

template<class T, class Node>
Treap<T, Node>::~Treap() {
}

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T, class Node>
void Treap<T, Node>::RightRotation(Node *&nodePtr) {
	Node *L = nodePtr->left;
	Node *temp = L->right;
	L->right = nodePtr;
	nodePtr->left = temp;
	nodePtr = L;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class T, class Node>
void Treap<T, Node>::LeftRotation(Node *&nodePtr) {
	Node *R = nodePtr->right;
	Node *temp = R->left;
	R->left = nodePtr;
	nodePtr->right = temp;
	nodePtr = R;
}

//*************************************************************
// insert accepts a TreeNode pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the TreeNode pointer. This function is called recursively. *
//*************************************************************
template<class T, class Node>
void Treap<T, Node>::insert(Node *&nodePtr, Node *&newNode) {
	if (nodePtr == nullptr) {
		nodePtr = newNode; // Insert the node.
		return;
	} else if (newNode->value < nodePtr->value)
		insert(nodePtr->left, newNode); // Search the left branch
	else
		insert(nodePtr->right, newNode); // Search the right branch

	if (nodePtr->left) {
		if (nodePtr->priority < nodePtr->left->priority)
			RightRotation(nodePtr);
	}
	if (nodePtr->right) {
		if (nodePtr->priority < nodePtr->right->priority)
			LeftRotation(nodePtr);
	}
}

//**********************************************************
// insertNode creates a new node to hold num as its value, *
// and passes it to the insert function.                   *
//**********************************************************
template<class T, class Node>
void Treap<T, Node>::insert(T item) {
	Node *newNode = nullptr; // Pointer to a new node.

	// Create a new node and store num in it.
	newNode = new Node;
	newNode->value = item;
//	newNode->priority = rand();
	newNode->priority = rand() % 1000;

	// Insert the node.
	insert(this->root, newNode);
}

//**********************************************
// remove calls deleteNode to delete the       *
// node whose value member is the same as num. *
//**********************************************
template<class T, class Node>
void Treap<T, Node>::remove(T item) {
	Node *parent = nullptr;
	deleteNodeFind(item, this->root, parent);
}

//********************************************
// deleteNode deletes the node whose value   *
// member is the same as num.                *
//********************************************
template<class T, class Node>
void Treap<T, Node>::deleteNodeFind(T item, Node *&nodePtr, Node *&parent) {
	if (!nodePtr)
		return;

	if (item < nodePtr->value)
		deleteNodeFind(item, nodePtr->left, nodePtr);
	else if (item > nodePtr->value)
		deleteNodeFind(item, nodePtr->right, nodePtr);
	else
		deleteNode(nodePtr, parent);
}

template<class T, class Node>
void Treap<T, Node>::deleteNode(Node *&nodePtr, Node *&parent) {
	if (!nodePtr)
		return;

	if (nodePtr->left && nodePtr->right) {
		if (nodePtr->left->priority > nodePtr->right->priority) {
			RightRotation(nodePtr);
			deleteNode(nodePtr->right, nodePtr);
		} else {
			LeftRotation(nodePtr);
			deleteNode(nodePtr->left, nodePtr);
		}
	} else if (nodePtr->left) {
		Node *ptr = nodePtr;
		if (parent) {
			if (parent->left == nodePtr)
				parent->left = nodePtr->left;
			else
				parent->right = nodePtr->left;
		} else {
			// nodePtr is the root.
			nodePtr = nodePtr->left;
		}
		delete ptr;
	} else if (nodePtr->right) {
		Node *ptr = nodePtr;
		if (parent) {
			if (parent->left == nodePtr)
				parent->left = nodePtr->right;
			else
				parent->right = nodePtr->right;
		} else {
			// nodePtr is the root.
			nodePtr = nodePtr->right;
		}
		delete ptr;
	} else {
		Node *ptr = nodePtr;
		nodePtr = nullptr;
		delete ptr;
	}
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T, class Node>
void Treap<T, Node>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template<class T, class Node>
void Treap<T, Node>::PrintTreeP(Node *t, int Indent, int Level) {
	if (t) {
		PrintTreeP(t->right, Indent, Level + 1);
		IndentBlock(Indent * Level);
		cout << t->value << "/" << t->priority << "\n";
		PrintTreeP(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template<class T, class Node>
void Treap<T, Node>::PrintTreeP(int Indent, int Level) {
	if (this->root)
		PrintTreeP(this->root, Indent, Level);
}

#endif /* TREAP_H_ */
