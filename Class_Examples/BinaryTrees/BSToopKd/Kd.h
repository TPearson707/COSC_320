#ifndef KD_H_
#define KD_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "BST.h"

using namespace std;

/*
 The templated type T is some container that has the indexing operator [], copy constructor,
 and assignment operator overloaded.  For the node we can use the generic TreeNode from BinaryTree.
 T must also have a function size() that returns the number of elements in the container.
 Ideally this is written for T to be a vector of a type that can be compared.
 We assume that the container objects all have the same number of elements in them
 for each node in the tree.
 */

template<class T, class Node = TreeNode<T>>
class KdTree: public BST<T, Node> {
protected:
	void deleteNode(Node*&, Node*&, int);
	void IndentBlock(int);
	void PrintTreeList(Node*, int, int);
	bool dataequal(const T &item1, const T &item2);
	void smallestNode(Node*&, Node*&, int, int&);
	bool isKd(Node*, int, int);

public:
	KdTree();
	virtual ~KdTree();

	void insert(T);
	void remove(T);

	virtual bool find(const T&);
	virtual Node* findNode(const T&);

	bool isKd();
	void PrintTreeList(int Indent = 4, int Level = 0);
};

template<class T, class Node>
KdTree<T, Node>::KdTree() {
}

template<class T, class Node>
KdTree<T, Node>::~KdTree() {
}

/*
 * Inserts a new node into the K-d tree.
 * First finds the position of insertion.
 * If the root is null it inserts in the root.
 * Otherwise it looks at the parent node and inserts into its correct child.
 */
template<class T, class Node>
void KdTree<T, Node>::insert(T newvals) {
	Node *ptr = this->root;
	Node *prev = nullptr;
	int level = 0;
	int lastlevel = 0;
	int size = newvals.size();

	while (ptr) {
		prev = ptr;
		if (newvals[level] < ptr->value[level])
			ptr = ptr->left;
		else
			ptr = ptr->right;
		lastlevel = level;
		level = (level + 1) % size;
	}

	Node *newnode = new Node;
	newnode->value = newvals;

	if (!this->root) {
		this->root = newnode;
	} else {
		if (newvals[lastlevel] < prev->value[lastlevel])
			prev->left = newnode;
		else
			prev->right = newnode;
	}
}

/*
 * Determines if the tree is a K-d tree.
 * This is the recursive counterpart that checks if the current node
 * pointer has the correct order with its childern and then
 * recurses on the children.
 */
template<class T, class Node>
bool KdTree<T, Node>::isKd(Node *ptr, int level, int size) {
	if (!ptr)
		return true;

	if (ptr->left && ptr->left->value[level] > ptr->value[level])
		return false;

	if (ptr->right && ptr->right->value[level] < ptr->value[level])
		return false;

	return isKd(ptr->left, (level + 1) % size, size)
			&& isKd(ptr->right, (level + 1) % size, size);
}

/*
 * Determines if the tree is a K-d tree.
 * Simply calls the recursive version on the root.
 */
template<class T, class Node>
bool KdTree<T, Node>::isKd() {
	if (!this->root)
		return true;

	return isKd(this->root, 0, this->root->value.size());
}

/*
 * Top function of the deletion chain.  Takes an item, determines if the item is in the
 * tree, if so it calls the deleteNode function on the node to be removed.
 * If the item is not in the tree the while loop will end with a ptr = nullptr.
 * The reason for rewriting the find code and not calling the find function is that
 * we need to track the level of the deleted node.
 */
template<class T, class Node>
void KdTree<T, Node>::remove(T item) {
	Node *ptr = this->root;
	Node *parent = nullptr;
	int level = 0;
	int size = item.size();

	while (ptr) {
		if (dataequal(item, ptr->value)) {
			deleteNode(ptr, parent, level);
			return;
		} else if (item[level] < ptr->value[level]) {
			parent = ptr;
			ptr = ptr->left;
		} else {
			parent = ptr;
			ptr = ptr->right;
		}
		level = (level + 1) % size;
	}
}

/*
 * Main deletion function of the tree node. In general, finds the smallest node value of the right tree
 * replaces the node to be remove bu this node (in value, delete by copy) and recurses to delete
 * the node that was copied from.  If there is no right tree it finds the smallest value of the
 * left tree and swaps the right tree with the left.  Once the recursion reaches a leaf, the leaf
 * is deleted.
 */
template<class T, class Node>
void KdTree<T, Node>::deleteNode(Node *&delnode, Node *&parent, int level) {
	int size = delnode->value.size();
	Node *snode, *snodep;
	int snodelevel = level;

	if (!delnode->left && !delnode->right) {
		if (parent) {
			if (parent->left == delnode)
				parent->left = nullptr;
			else
				parent->right = nullptr;
		}
		delete delnode;
		delnode = nullptr;
		return;
	} else if (delnode->right) {
		snode = delnode->right;
		snodep = delnode;
		snodelevel = (level + 1) % size;
		smallestNode(snode, snodep, level, snodelevel);
	} else {
		snode = delnode->left;
		snodep = delnode;
		snodelevel = (level + 1) % size;
		smallestNode(snode, snodep, level, snodelevel);
		delnode->right = delnode->left;
		delnode->left = nullptr;
	}
	delnode->value = snode->value;
	deleteNode(snode, snodep, snodelevel);
}

/*
 * Finds the smallest node in the tree from ptr.  Returns as node parameters the smallest
 * node, its parent, and its level.
 */
template<class T, class Node>
void KdTree<T, Node>::smallestNode(Node *&ptr, Node *&parent, int dislevel,
		int &currentlevel) {
	Node *snode = ptr;
	Node *snodep = parent;
	int snodelevel = currentlevel;
	int tempsnodelevel = snodelevel;
	int size = ptr->value.size();

	if (dislevel == currentlevel) {
		if (ptr->left) {
			Node *tempsnode = ptr->left;
			Node *tempsnodep = ptr;
			snodelevel = (currentlevel + 1) % size;
			smallestNode(tempsnode, tempsnodep, dislevel, snodelevel);
		} else {
			return;
		}
	}

	if (ptr->left) {
		Node *tempsnode = ptr->left;
		Node *tempsnodep = ptr;
		snodelevel = (currentlevel + 1) % size;
		smallestNode(tempsnode, tempsnodep, dislevel, snodelevel);
		if (snode->value[dislevel] >= tempsnode->value[dislevel]) {
			snode = tempsnode;
			snodep = tempsnodep;
			tempsnodelevel = snodelevel;
		}
	}

	if (ptr->right) {
		Node *tempsnode = ptr->right;
		Node *tempsnodep = ptr;
		snodelevel = (currentlevel + 1) % size;
		smallestNode(tempsnode, tempsnodep, dislevel, snodelevel);
		if (snode->value[dislevel] >= tempsnode->value[dislevel]) {
			snode = tempsnode;
			snodep = tempsnodep;
			tempsnodelevel = snodelevel;
		}
	}

	ptr = snode;
	parent = snodep;
	currentlevel = tempsnodelevel;
}

/*
 * Determines if all the values in the items are equal.  This allows the templeated type T
 * not to need an overloaded == .
 */
template<class T, class Node>
bool KdTree<T, Node>::dataequal(const T &item1, const T &item2) {
	int size = item1.size();
	bool found = true;
	for (int i = 0; i < size; i++) {
		if (item1[i] != item2[i])
			found = false;
	}
	return found;
}

/*
 * Function to determine if an element is in the tree.
 */
template<class T, class Node>
bool KdTree<T, Node>::find(const T &item) {
	return findNode(item) != nullptr;
}

/*
 * Function to determine if an element is in the tree, if so it returns the node containing
 * the item.
 */
template<class T, class Node>
Node* KdTree<T, Node>::findNode(const T &item) {
	Node *ptr = this->root;
	int level = 0;
	int size = item.size();

	while (ptr) {
		if (dataequal(item, ptr->value))
			return ptr;
		else if (item[level] < ptr->value[level])
			ptr = ptr->left;
		else
			ptr = ptr->right;
		level = (level + 1) % size;
	}

	return nullptr;
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************

template<class T, class Node>
void KdTree<T, Node>::IndentBlock(int num) {
	for (int i = 0; i < num; i++)
		cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************

template<class T, class Node>
void KdTree<T, Node>::PrintTreeList(Node *t, int Indent, int Level) {
	if (t) {
		PrintTreeList(t->right, Indent, Level + 1);

		IndentBlock(Indent * Level);
		for (unsigned int i = 0; i < t->value.size(); i++)
			cout << t->value[i] << " ";
		cout << "\n";

		PrintTreeList(t->left, Indent, Level + 1);
	}
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************

template<class T, class Node>
void KdTree<T, Node>::PrintTreeList(int Indent, int Level) {
	if (this->root)
		PrintTreeList(this->root, Indent, Level);
}

#endif /* KD_H_ */
