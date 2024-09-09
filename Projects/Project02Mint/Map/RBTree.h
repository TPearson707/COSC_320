/*
 * Created by: Don Spickler
 * Modified by: Thomas Pearson
 * Date of Creation: N/A
 * Date of Last Update: 04/24/2024
 */
#ifndef RBTREE_H
#define RBTREE_H

using namespace std;

enum color_t {
    RED, BLACK
};

template<class K, class V>
class RBTreeNode {
public:
    K key;
    V value;
    color_t color;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode *parent;

    RBTreeNode() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = RED;
    }

    RBTreeNode(K key, V val, color_t col, RBTreeNode *l, RBTreeNode *r, RBTreeNode *p) {
		this->key = key;
        value = val;
        left = l;
        right = r;
        parent = p;
        color = col;
    }
};

template<class K, class V>
class RBTree {
protected:
    RBTreeNode<K, V> *root;
    RBTreeNode<K, V> *NIL;
    void IndentBlock(int num);
    void PrintTree(RBTreeNode<K, V>*, int, int);

    void LeftRotation(RBTreeNode<K, V>*);
    void RightRotation(RBTreeNode<K, V>*);
    void insertFix(RBTreeNode<K, V>*);

    void transplant(RBTreeNode<K, V>*, RBTreeNode<K, V>*);
    void deleteFix(RBTreeNode<K, V>*);
    RBTreeNode<K, V>* getMinNode(RBTreeNode<K, V>*);

    void destroySubTree(RBTreeNode<K, V>*);

	RBTreeNode<K, V>* copyTree(RBTreeNode<K, V>* nodePtr, RBTreeNode<K, V>* nodeNIL);
	bool checkEqual(RBTreeNode<K, V>*, RBTreeNode<K, V>*, RBTreeNode<K, V>*);

public:
    RBTree();
    virtual ~RBTree();
	RBTree(const RBTree<K, V> & obj);

    void insert(K, V);
    void remove(K);

    bool find(const K&);
    RBTreeNode<K, V>* findNode(const K&);

    void PrintTree(int Indent = 4, int Level = 0);

	RBTree<K, V> & operator=(const RBTree<K, V> &);
	bool operator==(RBTree<K, V> &);
};

template<class K, class V>
RBTree<K, V>::RBTree() {
    NIL = new RBTreeNode<K, V>(K(), V(), BLACK, nullptr, nullptr, nullptr);
    root = NIL;
}

template<class K, class V>
RBTree<K, V>::~RBTree() {
    destroySubTree(root);
    delete NIL;
}

/*
 * Description: Copy constructor for rbtree class
 * Parameters: const RBTree<K, V> & obj
 * Return Type: None
*/
template<class K, class V>
RBTree<K, V>::RBTree(const RBTree<K, V> & obj) {
	NIL = new RBTreeNode<K, V>(K(), V(), BLACK, nullptr, nullptr, nullptr);
	root = NIL;

	root = copyTree(obj.root, obj.NIL);
}

/*
 * Description: Helper function to copy a tree into another tree
 * Parameters: RBTreeNode<K, V>* nodePtr, RBTreeNode<K, V>* nodeNIL
 * Return Type: RBTreeNode<K, V>*
*/
template<class K, class V>
RBTreeNode<K, V>* RBTree<K, V>::copyTree(RBTreeNode<K, V>* nodePtr, RBTreeNode<K, V>* nodeNIL) {
	if (nodePtr == nodeNIL)
		return NIL;

	insert(nodePtr->key, nodePtr->value);
	copyTree(nodePtr->left, nodeNIL);
	copyTree(nodePtr->right, nodeNIL);

	return root;
}

/*
 * Recursively frees the memory of the subtree pointed to by nodePtr.
 */
template<class K, class V>
void RBTree<K, V>::destroySubTree(RBTreeNode<K, V> *nodePtr) {
    if (nodePtr != NIL) {
        if (nodePtr->left != NIL)
            destroySubTree(nodePtr->left);
        if (nodePtr->right != NIL)
            destroySubTree(nodePtr->right);
        delete nodePtr;
    }
}

/*
 * Inserts a new node into the RB-Tree as with a standard BST but then calls the
 * insertFix function to adjust the tree back to an RB tree.
 */
template<class K, class V>
void RBTree<K, V>::insert(K key, V val) {
    RBTreeNode<K, V> *newnode = new RBTreeNode<K, V>(key, val, RED, NIL, NIL, NIL);
    RBTreeNode<K, V> *y = NIL;
    RBTreeNode<K, V> *x = root;

    while (x != NIL) {
		if (x->key == key) {
			x->value = val;
			delete newnode;
			return;
		}

        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    newnode->parent = y;
    if (y == NIL)
        root = newnode;
    else if (newnode->key < y->key)
        y->left = newnode;
    else
        y->right = newnode;

    insertFix(newnode);
}

/*
 * Adjusts the tree back to an RB tree after insertion of a new node.
 */
template<class K, class V>
void RBTree<K, V>::insertFix(RBTreeNode<K, V> *z) {
    RBTreeNode<K, V> *y = NIL;

    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotation(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotation(z->parent->parent);
            }
        } else {
            y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotation(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotation(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

/*
 * This is a helper function to the node deletion process.
 */
template<class K, class V>
void RBTree<K, V>::transplant(RBTreeNode<K, V> *u, RBTreeNode<K, V> *v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

/*
 * Finds the smallest node in the subtree pointed to by x.  As usual
 * we traverse down the left branch as far as possible.  The node y
 * tracks x's parent so that when x == NIL, y is the minimum valued
 * node.
 */
template<class K, class V>
RBTreeNode<K, V>* RBTree<K, V>::getMinNode(RBTreeNode<K, V> *x) {
    if (x == NIL)
        return NIL;

    RBTreeNode<K, V> *y = NIL;
    while (x != NIL) {
        y = x;
        x = x->left;
    }
    return y;
}

/*
 * Finds and deletes the node whose value is val.  Calls the deleteFix function
 * to readjust the tree back to RB format.
 */
template<class K, class V>
void RBTree<K, V>::remove(K key) {
    RBTreeNode<K, V> *z = findNode(key);
    if (z == NIL)
        return;

    RBTreeNode<K, V> *y = z;
    RBTreeNode<K, V> *x = NIL;
    color_t yorigcol = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = getMinNode(z->right);
        yorigcol = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yorigcol == BLACK)
        deleteFix(x);
}

/*
 * Readjusts the RB tree to fix any violated properties after the deletion of a
 * node.
 */
template<class K, class V>
void RBTree<K, V>::deleteFix(RBTreeNode<K, V> *x) {
    RBTreeNode<K, V> *w = NIL;

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                LeftRotation(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotation(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotation(x->parent);
                x = root;
            }
        } else {
            w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                RightRotation(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotation(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotation(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

/*
 * This returns true if the item is in the RB-tree and false otherwise.
 * It simply calls the node based recursive version and checks the result
 * against the NIL object.
 */
template<class K, class V>
bool RBTree<K, V>::find(const K &item) {
    return findNode(item) != NIL;
}

/*
 Does a right rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 x --- pointer to the node to rotate right around.
 */

template<class K, class V>
void RBTree<K, V>::RightRotation(RBTreeNode<K, V> *x) {
	RBTreeNode<K, V> *y = x->left;
	x->left = y->right;

	if (y->right != NIL)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

/*
 Does a left rotation at the input node.
 The function also updates the height values for the nodes.

 Parameters
 nodePtr --- pointer to the node to rotate right around.
 */

template<class K, class V>
void RBTree<K, V>::LeftRotation(RBTreeNode<K, V> *x) {
	RBTreeNode<K, V> *y = x->right;
	x->right = y->left;

	if (y->left != NIL)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == NIL)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}


/*
 * Recursive find function that finds the first node containing the value item.
 */
template<class K, class V>
RBTreeNode<K, V>* RBTree<K, V>::findNode(const K &item) {
    RBTreeNode<K, V> *nodePtr = root;

    while (nodePtr != NIL) {
        if (nodePtr->key == item)
            return nodePtr;
        else if (item < nodePtr->key)
            nodePtr = nodePtr->left;
        else
            nodePtr = nodePtr->right;
    }
    return NIL;
}

//****************************************************************
// Simple helper function to do the indentations for the tree
// printing algorithm.
//****************************************************************
template<class K, class V>
void RBTree<K, V>::IndentBlock(int num) {
    for (int i = 0; i < num; i++)
        cout << " ";
}

//****************************************************************
// This function recursively prints the tree contents to the
// console using a reverse inorder traversal with indenting.
// This includes the height and balance factor of each node.
//****************************************************************
template<class K, class V>
void RBTree<K, V>::PrintTree(RBTreeNode<K, V> *t, int Indent, int Level) {
    if (t != NIL) {
        PrintTree(t->right, Indent, Level + 1);

        string RBstr;
        if (t->color == RED)
            RBstr = "R";
        else
            RBstr = "B";

        IndentBlock(Indent * Level);
        cout << t->value << " (" << RBstr << ")" << endl;

        PrintTree(t->left, Indent, Level + 1);
    }
}

//****************************************************************
// This function initiates the recursive printing function to
// print the contents of the tree in tree form sideways with the
// root at the far left. This includes the height and balance
// factor of each node.
//****************************************************************
template<class K, class V>
void RBTree<K, V>::PrintTree(int Indent, int Level) {
    if (root)
        PrintTree(root, Indent, Level);
}

/*
 * Description: Helper function that checks if a tree is equal to another tree
 * Parameters: RBTreeNode<K, V>* nodePtr, RBTreeNode<K, V>* obj, RBTreeNode<K, V>* nodeNIL
 * Return Type: bool
*/
template <class K, class V>
bool RBTree<K, V>::checkEqual(RBTreeNode<K, V>* nodePtr, RBTreeNode<K, V>* obj, RBTreeNode<K, V>* nodeNIL) {

	if (nodePtr == NIL && obj == nodeNIL)
		return true;

    if (nodePtr == NIL || obj == nodeNIL)
		return false;

	if (nodePtr->key != obj->key)
		return false;

    if (nodePtr->value != obj->value)
		return false;

    return checkEqual(nodePtr->left, obj->left, nodeNIL) && checkEqual(nodePtr->right, obj->right, nodeNIL);

}


/*
 * Description: overloaded assignmnet operator for rbtree class
 * Parameters: const RBTree<T> & rhs
 * Return Type: bool
*/
template<class K, class V>
RBTree<K, V> & RBTree<K, V>::operator=(const RBTree<K, V> & rhs) {
	copyTree(rhs.root, rhs.NIL);
	return *this;
}

/*
 * Description: Overloaded == operator for the rbtree class
 * Parameters: RBTree<K, V> & rhs
 * Return Type: bool
*/
template <class K, class V>
bool RBTree<K, V>::operator==(RBTree<K, V> & rhs) {
	return checkEqual(root, rhs.root, rhs.NIL);
}

#endif // RBTREE_H
