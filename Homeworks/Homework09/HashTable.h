#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include "ListOfLists.h"

using namespace std;

template <class T> class HashTable {
protected:
  int size = 0;
  ListOfLists<T> table;
  int (*hf)(T &);
public:
  HashTable(int sz, int (*hashfct)(T &));
  virtual ~HashTable();
  void insert(T);
  void remove(T);
  bool find(T);
  void rehash(int sz);
  void print();
};

template <class T>
HashTable<T>::HashTable(int sz, int (*hashfct)(T &)) {
  size = sz;
  hf = hashfct;
  table.addRows(size);
}

template <class T> HashTable<T>::~HashTable() {}


template <class T> void HashTable<T>::insert(T item) {
  int pos = hf(item) % size;
  table[pos].push_back(item);
}


template <class T> void HashTable<T>::remove(T item) {
  int pos = hf(item) % size;

  for (size_t i = 0; i < table[pos].size(); i++)
    if (table[pos][i] == item)
      table[pos].erase(table[pos].begin() + i);
}


template <class T> bool HashTable<T>::find(T item) {
  int pos = hf(item) % size;

  for (size_t i = 0; i < table[pos].size(); i++)
    if (table[pos][i] == item)
      return true;

  return false;
}


template <class T> void HashTable<T>::rehash(int sz) {
  size = sz;
  ListOfLists<T> newTable;
  newTable.addRows(size);
  vector<T> temp;

  for (size_t i = 0; i < table.size(); i++)
    for (size_t j = 0; j < table[i].size(); j++)
      if (table[i][j])
        temp.push_back(table[i][j]);

  table = newTable;

  for (size_t i = 0; i < temp.size(); i++)
    insert(temp[i]);
}

template <class T> void HashTable<T>::print() {
  for (size_t i = 0; i < table.size(); i++) {
    cout << i << ": ";
    for (size_t j = 0; j < table[i].size(); j++)
      cout << table[i][j] << " ";
    cout << endl;
  }
}

#endif /* HASHTABLE_H_ */
