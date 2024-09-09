/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 04/17/2024
 * Date of Last Update: 04/23/2024
 * Description: Set class inherited from RBTree.h
*/

#ifndef SET_H
#define SET_H

#include <vector>

#include "RBTree.h"

template <class T>
class Set : public RBTree<T> {
    private:
        int size(RBTreeNode<T>*);
        void toVector(RBTreeNode<T>*, vector<T> &);
        void toArray(RBTreeNode<T>*, T* &, int, int &);
        bool arrEmpty(T* &, int);
        void copyTreeInorder(RBTreeNode<T>*);
        bool checkAStrictSubsetB(RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, Set<T>&);
        bool checkBStrictSubsetA(RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, RBTreeNode<T>*, Set<T>&);
    public:

        Set();
        ~Set();
        Set (const Set<T> &);

        bool empty();
        int size();
        void clear();
        void insert(T);
        void erase(T);
        bool find(T);
        void toVector(vector<T> &);
        void toArray(T* & , int);

        void print(); // kill later

        Set<T> & operator=(const Set<T> &);

        bool operator==(Set<T> &);
        bool operator!=(Set<T> &);
        bool operator<(Set<T> &);
        bool operator>(Set<T> &);
        bool operator<=(Set<T> &);
        bool operator>=(Set<T> &);
        Set operator+(Set<T> &);
        Set operator*(Set<T> &);
        Set operator-(Set<T> &);

        template <class U>
        friend ostream& operator<<(ostream&, Set<U>&);
};

/*
 * Description: Constructor for set class
 * Parameters: None
 * Return Type: None
*/
template <class T>
Set<T>::Set() {

}

/*
 * Description: Destructor for set class
 * Parameters: None
 * Return Type: None
*/
template <class T>
Set<T>::~Set() {

}

/*
 * Description: Copy constructor for set class
 * Parameters: const Set<T> & obj
 * Return Type: None
*/
template <class T>
Set<T>::Set(const Set<T> & obj) : RBTree<T>(obj) {

}

template <class T>
void Set<T>::copyTreeInorder(RBTreeNode<T>* nodePtr) {
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
bool Set<T>::empty() {
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
int Set<T>::size(RBTreeNode<T>* nodePtr) {
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
int Set<T>::size() {    
    return size(this->root);
}

/*
 * Description: clears the elements in the set
 * Parameters: None
 * Return Type: void
*/
template <class T>
void Set<T>::clear() {
    RBTree<T>::destroySubTree(this->root);
    this->root = this->NIL;
}

/*
 * Description: if a value is already in the set does nothing, if the value is not then the value is inserted into the set
 * Parameters: T value
 * Return Type: void
*/
template <class T>
void Set<T>::insert(T value) {
    RBTree<T>::insert(value);
}

/*
 * Description: erases an inputted value from the set
 * Parameters: T value
 * Return Type: None
*/
template <class T>
void Set<T>::erase(T value) {
    RBTree<T>::remove(value);
}

/*
 * Description: Searches the set for a value, if value is present return true, if not return false.
 * Parameters: T value
 * Return Type: bool
*/
template <class T>
bool Set<T>::find(T value) {
    return RBTree<T>::find(value);
}

/*
 * Description: driver functoin for toVector
 * Parameters: RBTreeNode<T>* nodePtr, vector<T> & vect
 * Return Type: void
*/
template <class T>
void Set<T>::toVector(RBTreeNode<T>* nodePtr, vector<T> & vect) {
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
void Set<T>::toVector(vector<T> & vect) {
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
void Set<T>::toArray(RBTreeNode<T>* nodePtr, T* & arr, int size, int & index) {
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
void Set<T>::toArray(T* & arr, int size) {

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
bool Set<T>::arrEmpty(T* & arr, int size) {
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
Set<T> & Set<T>::operator=(const Set<T> & rhs) {
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
bool Set<T>::operator==(Set<T> & rhs) {

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
bool Set<T>::operator!=(Set<T> & rhs) {
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
bool Set<T>::operator<(Set<T> & rhs) {
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
bool Set<T>::checkAStrictSubsetB(RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, Set<T>& rhs) {
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
bool Set<T>::operator>(Set<T> & rhs) {
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
bool Set<T>::checkBStrictSubsetA(RBTreeNode<T>* nodePtr, RBTreeNode<T>* rhsPtr, RBTreeNode<T>* rhsNIL, RBTreeNode<T>* NIL, Set<T>& rhs) {

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
bool Set<T>::operator<=(Set<T> & rhs) {
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
bool Set<T>::operator>=(Set<T> & rhs) {
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
Set<T> Set<T>::operator+(Set<T> & rhs) {
    Set<T> set;

    vector<T> vect1;
    vector<T> vect2;

    this->toVector(vect1);
    rhs.toVector(vect2);

    for (unsigned int i = 0; i < vect1.size(); i++)
        set.insert(vect1[i]);

    for (unsigned int i = 0; i < vect2.size(); i++)
        set.insert(vect2[i]);

    return set;
}

/*
 * Description: Overloaded multiplication operator, returns the intersection of two sets
 * Parameters: Set<T> & rhs
 * Return Type: Set<T>
*/
template <class T>
Set<T> Set<T>::operator*(Set<T> & rhs) {
    Set<T> set;

    vector<T> vect1;
    vector<T> vect2;

    this->toVector(vect1);
    rhs.toVector(vect2);

    int minimum = min(vect1.size(), vect2.size());

    if (minimum == vect1.size()) {
        for (int i = 0; i < minimum; i++)
            for (int j = 0 ; j < vect2.size(); j++)
                if (vect1[i] == vect2[j])
                    set.insert(vect1[i]);
    } else {
        for (int i = 0; i < minimum; i++)
            for (int j = 0; j < vect1.size(); j++)
                if(vect2[i] == vect1[j])
                    set.insert(vect2[i]);
    }

    return set;

}

/*
 * Description: Overloaded subtraction operator to take the difference of two sets
 * Parameters: Set<T> & rhs
 * Return Type:  Set<T>
*/
template <class T>
Set<T> Set<T>::operator-(Set<T> & rhs) {
    Set<T> set;

    vector<T> vect1;

    this->toVector(vect1);

    for (unsigned int i = 0; i < vect1.size(); i++) {
        if (!(rhs.find(vect1[i])))
            set.insert(vect1[i]);
    }

    return set;
}


/*
 * Description: overloaded insertion operator
 * Parameters: ostream& os, Set<T>& set
 * Return Type: ostream&
*/

template <class T>
ostream& operator<<(ostream& os, Set<T>& set) {
    if(set.empty()) {
        os << "Cannot print an empty map";
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
