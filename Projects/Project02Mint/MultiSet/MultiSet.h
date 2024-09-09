/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 04/23/2024
 * Date of Last Update: 04/23/2024
 * Description: MultiSet class inherited from RBTree.h
*/

#ifndef MULTISET_H
#define MULTISET_H

#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

#include "RBTree.h"

template <class T>
class MultiSet : public RBTree<T> {
    private:
        int size(RBTreeNode<T>*);
        void toVector(RBTreeNode<T>*, vector<T> &);
        void toArray(RBTreeNode<T>*, T* &, int, int &);
        bool arrEmpty(T* &, int);
        void copyTreeInorder(RBTreeNode<T>*);
        bool checkAStrictSubsetB(RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, MultiSet<T>&);
        bool checkBStrictSubsetA(RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, MultiSet<T>&);
    public:

        MultiSet();
        ~MultiSet();
        MultiSet (const MultiSet<T> &);

        bool empty();
        int size();
        void clear();
        void insert(T);
        void erase(T);
        int count(T);
        bool find(T);
        void toVector(vector<T> &);
        void toArray(T* & , int);

        void print(); // kill later

        MultiSet<T> & operator=(const MultiSet<T> &);

        bool operator==(MultiSet<T> &);
        bool operator!=(MultiSet<T> &);
        bool operator<(MultiSet<T> &);
        bool operator>(MultiSet<T> &);
        bool operator<=(MultiSet<T> &);
        bool operator>=(MultiSet<T> &);
        MultiSet operator+(MultiSet<T> &);
        MultiSet operator*(MultiSet<T> &);
        MultiSet operator-(MultiSet<T> &);

        template <class U>
        friend ostream& operator<<(ostream&, MultiSet<U>&);
};

/*
 * Description: Constructor for set class
 * Parameters: None
 * Return Type: None
*/
template <class T>
MultiSet<T>::MultiSet() {

}

/*
 * Description: Destructor for set class
 * Parameters: None
 * Return Type: None
*/
template <class T>
MultiSet<T>::~MultiSet() {

}

/*
 * Description: Copy constructor for set class
 * Parameters: const Set<T> & obj
 * Return Type: None
*/
template <class T>
MultiSet<T>::MultiSet(const MultiSet<T> & obj) : RBTree<T>(obj) {

}

template <class T>
void MultiSet<T>::copyTreeInorder(RBTreeNode<T>* nodePtr) {
        if (nodePtr != this->NIL) {
            copyTreeInorder(nodePtr->left);
            this->insert(nodePtr->value);
            copyTreeInorder(nodePtr->right);
        }
}

/*
 * Description: checks to see if the set is empty or not
 * Parameters: None
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::empty() {
    if (this->root == this->NIL)
        return true;

    return false; 
}

/*
 * Description: Recursively gets the number of elements in the set
 * Parameters: RBTreeNode<T>* nodePtr
 * Return Type: int
*/
template <class T>
int MultiSet<T>::size(RBTreeNode<T>* nodePtr) {
    if (nodePtr == this->NIL)
        return 0;

    return 1 + size(nodePtr->left) + size(nodePtr->right);
}

/*
 * Description: Calls the recursive size function and returns the result
 * Parameters: None
 * Return Type: int
*/
template <class T>
int MultiSet<T>::size() {
    return size(this->root);
}

/*
 * Description: clears the elements in the set
 * Parameters: None
 * Return Type: void
*/
template <class T>
void MultiSet<T>::clear() {
    RBTree<T>::destroySubTree(this->root);
    this->root = this->NIL;
}

/*
 * Description: if a value is already in the set does nothing, if the value is not then the value is inserted into the set
 * Parameters: T value
 * Return Type: void
*/
template <class T>
void MultiSet<T>::insert(T value) {
    RBTree<T>::insert(value);
}

/*
 * Description: erases an inputted value from the set
 * Parameters: T value
 * Return Type: None
*/
template <class T>
void MultiSet<T>::erase(T value) {
    RBTree<T>::remove(value);
}

template <class T>
int MultiSet<T>::count(T key) {
    vector<T> vect;
    this->toVector(vect);
    int counter = 0;
    for (unsigned int i = 0; i < vect.size(); i++)
        if (vect[i] == key)
            counter++;

    return counter;
}

/*
 * Description: Searches the set for a value, if value is present return true, if not return false.
 * Parameters: T value
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::find(T value) {
    return RBTree<T>::find(value);
}

/*
 * Description: driver functoin for toVector
 * Parameters: RBTreeNode<T>* nodePtr, vector<T> & vect
 * Return Type: void
*/
template <class T>
void MultiSet<T>::toVector(RBTreeNode<T>* nodePtr, vector<T> & vect) {
    if (nodePtr != this->NIL) {
        toVector(nodePtr->left, vect);
        vect.push_back(nodePtr->value);
        toVector(nodePtr->right, vect);
    }
}

/*
 * Description: takes in a vector for reference and inserts the set into it sorted in ascending order.
 * Parameters: vector<T> & vect
 * Return Type: void
*/
template <class T>
void MultiSet<T>::toVector(vector<T> & vect) {
    if (!vect.empty())
        vect.clear();

    toVector(this->root, vect);
}

/*
 * Description: driver function for toArray
 * Parameters: RBTreeNode<T>* nodePtr, T* & arr, int size, int & index
 * Return Type: void
*/
template <class T>
void MultiSet<T>::toArray(RBTreeNode<T>* nodePtr, T* & arr, int size, int & index) {
    if (nodePtr != this->NIL) {
        toArray(nodePtr->left, arr, size, index);
        arr[index++] = nodePtr->value;
        toArray(nodePtr->right, arr, size, index);
    }
}

/*
 * Description: converts a set to an array
 * Parameters: T* & arr, int size
 * Return Type: void
*/
template <class T>
void MultiSet<T>::toArray(T* & arr, int size) {

    if (!arrEmpty(arr, size)) {
        delete[] arr;
        arr = new T[size]();
    }

    int index = 0;

    toArray(this->root, arr, size, index);
}

/*
 * Description: checks if an array is empty
 * Parameters: T* & arr, int size
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::arrEmpty(T* & arr, int size) {
    for (int i = 0; i < size; i++)
        if (arr[i] > 0 || arr[i] < 0)
            return false;

    return true;

}

/*
 * Description: overloaded assignment operator for set class
 * Parameters: const Set<T> & rhs
 * Return Type: bool
*/
template <class T>
MultiSet<T> & MultiSet<T>::operator=(const MultiSet<T> & rhs) {
    this->clear();
    RBTree<T>::operator=(rhs);
    return *this;
}

/*
 * Description: overloaded == operator for set class
 * Parameters: set<T> & rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator==(MultiSet<T> & rhs) {

    if (this->size() != rhs.size())
        return false;

    return RBTree<T>::operator==(rhs);
}

/*
 * Description: overloaded != for set class
 * Parameters: Set<T> & rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator!=(MultiSet<T> & rhs) {
    if (this->size() != rhs.size())
        return true;

    return !RBTree<T>::operator==(rhs);
}

/*
 * Description: overloaded < operator for set class, returns true is A is a strict subset of B
 * Parameters: Set<T> & rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator<(MultiSet<T> & rhs) {
    if (this->size() >= rhs.size())
        return false;

    return checkAStrictSubsetB(this->root, rhs.root, rhs.NIL, this->NIL, rhs);
}

/*
 * Description: Helper function for > and >=, returns true if A is a subset of B (operator evaluates strict)
 * Parameters: RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, Set<T>& rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::checkAStrictSubsetB(RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, MultiSet<T>& rhs) {
    if (nodePtr == NIL)
        return true;

    if (!rhs.find(nodePtr->value))
        return false;

    return checkAStrictSubsetB(nodePtr->left, rhsPtr, rhsNIL, NIL, rhs) && checkAStrictSubsetB(nodePtr->right, rhsPtr, rhsNIL, NIL, rhs);
}

/*
 * Description: Overloaded > operator, returns true is B is a strict subset of A
 * Parameters: Set<T>& rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator>(MultiSet<T> & rhs) {
    if (size() <= rhs.size())
        return false;

    return checkBStrictSubsetA(this->root, rhs.root, rhs.NIL, this->NIL, rhs);
}

/*
 * Description: Helper function for > and >=, returns true if B is a subset of A (operator evaluates strict)
 * Parameters: RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, Set<T>& rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::checkBStrictSubsetA(RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, MultiSet<T>& rhs) {

    if (nodePtr == NIL)
        return true;

    if (!find(rhsPtr->value))
        return false;

    return checkBStrictSubsetA(nodePtr->left, rhsPtr, rhsNIL, NIL, rhs) && checkBStrictSubsetA(nodePtr->right, rhsPtr, rhsNIL, NIL, rhs);
}

/*
 * Description: Overloaded <= operator, returns true is A is a subset of B
 * Parameters: Set<T> & rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator<=(MultiSet<T> & rhs) {
    if (size() > rhs.size())
        return false;

    return checkBStrictSubsetA(this->root, rhs.root, rhs.NIL, this->NIL, rhs);
}

/*
 * Description: overloaded >= operator, returns true is B is a subset of A
 * Parameters: Set<T>& rhs
 * Return Type: bool
*/
template <class T>
bool MultiSet<T>::operator>=(MultiSet<T> & rhs) {
    if (size() < rhs.size())
        return false;

    return checkBStrictSubsetA(this->root, rhs.root, rhs.NIL, this->NIL, rhs);
}

/*
 * Description: Overloaded addition operator, returns the union of two sets
 * Parameters: Set<T>& rhs
 * Return Type: Set<T>
*/
template <class T>
MultiSet<T> MultiSet<T>::operator+(MultiSet<T> & rhs) {
    MultiSet<T> set;
    vector<T> elements;
    vector<T> rhsElements;
    this->toVector(elements);
    rhs.toVector(rhsElements);

    for (unsigned int i = 0; i < elements.size(); i++) {

        int maxFrequency = max(this->count(elements[i]), rhs.count(elements[i]));

        if (set.count(elements[i]) != 0)
            continue;

        for (int j = 0; j < maxFrequency; j++) {
            set.insert(elements[i]);
        }
    }

    for (unsigned int i = 0; i < rhsElements.size(); i++) {

        int maxFrequency = max(this->count(rhsElements[i]), rhs.count(rhsElements[i]));

        if (set.count(rhsElements[i]) != 0)
            continue;

        for (int j = 0; j < maxFrequency; j++) {
            set.insert(rhsElements[i]);
        }
    }

    return set;
}

/*
 * Description: Overloaded multiplication operator, returns the intersection of two sets
 * Parameters: Set<T> & rhs
 * Return Type: Set<T>
*/
template <class T>
MultiSet<T> MultiSet<T>::operator*(MultiSet<T> & rhs) {
    MultiSet<T> set;
    vector<T> elements;
    this->toVector(elements);

    for (unsigned int i = 0; i < elements.size(); i++) {

        if (this->count(elements[i]) == 0 || rhs.count(elements[i]) == 0)
            continue;

        int minFrequency = min(this->count(elements[i]), rhs.count(elements[i]));

        if (set.count(elements[i]) != 0)
            continue;

        for (int j = 0; j < minFrequency; j++) {
            set.insert(elements[i]);
        }
    }

    return set;
}
/*
 * Description: Overloaded subtraction operator to take the difference of two sets
 * Parameters: Set<T> & rhs
 * Return Type:  Set<T>
*/
template <class T>
MultiSet<T> MultiSet<T>::operator-(MultiSet<T> & rhs) {
    MultiSet<T> set;
    vector<T> elements;

    this->toVector(elements);

    for (unsigned int i = 0; i < elements.size(); i++) {

        int frequencyDifference = abs(this->count(elements[i]) - rhs.count(elements[i]));

        if (!rhs.find(elements[i])) {
            set.insert(elements[i]);
            continue;
        }

        if (set.find(elements[i]))
            continue;

        if (this->count(elements[i]) > rhs.count(elements[i]))
            for (unsigned int j = 0; j < frequencyDifference; j++)
                set.insert(elements[i]);


    }

    return set;
}


/*
 * Description: overloaded insertion operator
 * Parameters: ostream& os, Set<T>& set
 * Return Type: ostream&
*/

template <class T>
ostream& operator<<(ostream& os, MultiSet<T>& set) {

    if (set.empty()) {
        os << "Cannot print an empty set";
        return os;
    }
    os << "{";

    vector<T> vect;
    set.toVector(vect);

    for (unsigned int i = 0; i < vect.size(); i++) {
        if (i == vect.size() - 1) {
            cout << vect[i];
        } else {
            cout << vect[i] << ", ";
        }
    }

    os << "}";

    return os;
}


#endif // SET_H
