/*
 * Created by: Thomas Pearson
 * Date of Creation: 04/24/2024
 * Date of Last Update: 04/24/2024
 */

#ifndef MULTIMAP_H
#define MULTIMAP_H

#include <iostream>
#include <vector>
#include <utility>
#include "RBTree.h"

using namespace std;

template <class K, class V>
class MultiMap : public RBTree<K, V> {
private:
    int size(RBTreeNode<K, V>*);
    void toVector(RBTreeNode<K,V>*, vector<pair<K, V>> &);
public:
    MultiMap();
    ~MultiMap();
    MultiMap(const MultiMap& obj);
    bool empty();
    int size();
    void clear();
    void insert(K key, V value);
    void erase(K key, V value);
    bool find(K key) ;
    V get(K key);
    void set(K key, V value);

    void toVector(vector<pair<K, V>> &);

    MultiMap<K, V> & operator=(const MultiMap<K, V> & rhs);

    bool operator==(MultiMap & rhs);
    bool operator!=(MultiMap & rhs);

    template <class T, class O>
    friend ostream & operator<<(ostream & os, MultiMap<K, V> & map);
};

template <class K, class V>
MultiMap<K, V>::MultiMap() {

}

template <class K, class V>
MultiMap<K, V>::~MultiMap() {

}

template <class K, class V>
MultiMap<K, V>::MultiMap(const MultiMap& obj) : RBTree<K, V>(obj) {

}

/*
 * Description: checks to see if a the map is empty
 * Parameters: None
 * Return Type: bool
*/
template <class K, class V>
bool MultiMap<K, V>::empty() {
    if (this->root == this->NIL)
        return true;

    return false;
}

/*
 * Description: Recursively gets the number of elements in the map
 * Parameters: RBTreeNode<K, V>* nodePtr
 * Return Type: int
*/
template <class K, class V>
int MultiMap<K, V>::size(RBTreeNode<K,V>* nodePtr) {
    if (nodePtr == this->NIL)
        return 0;

    return 1 + size(nodePtr->left) + size(nodePtr->right);
}

/*
 * Description: Calls the recursive size function and returns the result
 * Parameters: None
 * Return Type: int
*/
template <class K, class V>
int MultiMap<K, V>::size() {
    return size(this->root);
}

/*
 * Description: clears the elements in the map
 * Parameters: None
 * Return Type: void
*/
template <class K, class V>
void MultiMap<K, V>::clear() {
    RBTree<K, V>::destroySubTree(this->root);
    this->root = this->NIL;
}

/*
 * Description: If the key is already in the set overwrite value, otherwise insert new.
 * Parameters: K key V value
 * Return Type: void
*/
template <class K, class V>
void MultiMap<K, V>::insert(K key, V value) {
    RBTree<K, V>::insert(key, value);
}

/*
 * Description: erases an inputted key from the map
 * Parameters: K key
 * Return Type: None
*/
template <class K, class V>
void MultiMap<K, V>::erase(K key, V value) {
    RBTree<K, V>::remove(key, value);
}


template <class K, class V>
bool MultiMap<K, V>::find(K key) {
    return RBTree<K, V>::find(key);
}

/*
 * Description: returns the value associated with the inputted key, if the key isn't in on the map throws out_of_range exception
 * Parameters: K key
 * Return Type: V
 */
template <class K, class V>
V MultiMap<K, V>::get(K key) {

    if (this->find(key)) {
        RBTreeNode<K, V>* node;
        node = RBTree<K, V>::findNode(key);
        return node->value;
    } else {
        throw out_of_range("Key not in map");
    }

}

/*
 * Description: If the key is already in the set overwrite value, otherwise insert new.
 * Parameters: K key V value
 * Return Type: void
*/
template <class K, class V>
void MultiMap<K, V>::set(K key, V value) {
    RBTree<K, V>::insert(key, value);
};

template <class K, class V>
MultiMap<K, V> & MultiMap<K, V>::operator=(const MultiMap<K, V> & rhs) {
    this->clear();
    RBTree<K, V>::operator=(rhs);
    return *this;
}

/*
 * Description: overloaded == for comparing maps
 * Parameters: MultiMap<K, V> & rhs
 * Return Type: bool
 */
template <class K, class V>
bool MultiMap<K, V>::operator==(MultiMap<K, V> & rhs) {
    if (this->size() != rhs.size())
        return false;

    return RBTree<K, V>::operator==(rhs);
}

/*
 * Description: overloaded != for comparing maps
 * Parameters: MultiMap<K, V> & rhs
 * Return Type: bool
 */
template <class K, class V>
bool MultiMap<K, V>::operator!=(MultiMap<K, V> & rhs) {
    if (this->size() != rhs.size())
        return true;

    return !RBTree<K, V>::operator==(rhs);
}

/*
 * Description: driver function for toVector(vector<pair<K, V>> & vect). Converts a map into a vector of pairs
 * Parameters: RBTreeNode<K, V>* nodePtr, vector<pair<K, V>> & vect
 * Return Type: None
 */
template <class K, class V>
void MultiMap<K, V>::toVector(RBTreeNode<K, V>* nodePtr, vector<pair<K, V>> & vect) {
    if (nodePtr != this->NIL) {
        toVector(nodePtr->left, vect);
        vect.push_back(make_pair(nodePtr->key, nodePtr->value));
        toVector(nodePtr->right, vect);
    }
}

/*
 * Description: Helper function to convert a map to a vector
 * Parameters: vector<pair<K, V>> & vect
 * Return Type: None
 */
template <class K, class V>
void MultiMap<K, V>::toVector(vector<pair<K, V>> & vect) {
    if (!vect.empty())
        vect.clear();

    toVector(this->root, vect);
}

/*
 * Description: overloaded insertion operator that calls the toVector functions to return a vector of pairs for ease of printing
 * Parameters: ostream & os, MultiMap<K, V> & map
 * Return Type: ostrea &
 */
template <class K, class V>
ostream & operator<<(ostream & os, MultiMap<K, V> & map) {

    if (map.empty()) {
        os << "cannot print an empty map";
        return os;
    }
    vector<pair<K, V>> vect;
    map.toVector(vect);

    os << "{ ";

    for (unsigned int i = 0; i < vect.size() - 1; i++)
        cout << "(" << vect[i].first << ", " << vect[i].second << "), ";

    cout << "(" << vect[vect.size() - 1].first << ", " << vect[vect.size() - 1].second << ")";

    os << " }";

    return os;
}

#endif // MULTIMAP_H
