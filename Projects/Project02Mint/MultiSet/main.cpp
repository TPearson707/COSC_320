/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 04/23/2024
 * Date of Last Update: 04/23/2024
 * Description: Testing program for MultiSet class which is inherited from RBTree.h
*/

#include <iostream>
#include <cstdlib>
#include <vector>

#include "MultiSet.h"

using namespace std;

int main() {
    MultiSet<int> set;

    vector<int> vect;
    int* arr;
    arr = new int[5];

    cout << set.empty() << endl;
    set.insert(1);
    set.insert(4);
    set.insert(3);
    set.insert(10);
    set.insert(4);
    set.insert(8);
    MultiSet<int>set2(set);

    set2.insert(12);

    set2 = set;


    set.toVector(vect);
    set.toArray(arr, 5);
    cout << endl;
    cout << set.empty() << " " << set.size() << endl;
//     set.erase(4);
    cout << endl;
    cout << set.empty() << " " << set.size() << endl;
//     set.clear();
    cout << set.empty() << " " << set.size() << endl;

    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << " ";
    cout << endl;

    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
    cout << endl;

    vect.clear();
    set2.toVector(vect);

    for (int i = 0; i < 5; i++)
        cout << vect[i] << " ";
    cout << endl;

    cout << set.size() << " " << set2.size() << endl;
    if (set == set2)
        cout << "Sets are equal" << endl;
    else {
        cout << "Sets are not equal" << endl;
    }

    if (set != set2)
        cout << "Sets are equal" << endl;
    else {
        cout << "Sets are not equal" << endl;
    }
    delete [] arr;

    set2.insert(12);
    set.insert(13);

    cout << set.size() << " " << set2.size() << endl;

    if (set <= set2)
        cout << "set 1 is a strict subset of set 2" << endl;
    else {
        cout << "set 1 is not a strict subset of set 2" << endl;
    }

    if (set >= set2)
        cout << "set 2 is a strict subset of set 1" << endl;
    else {
        cout << "set 2 is not a strict subset of set 1" << endl;
    }
    MultiSet<int> set3;

    cout << set2 << endl;
    cout << set3<< endl;

    cout << set.count(4) << endl;
    cout << set2.count(4) << endl;
    cout << set3.count(4) << endl;

    cout << set2.count(4)<< endl;

    cout << set << endl;
    cout << set2<< endl;

    set3 = set * set2;

    cout << set << endl;
    cout << set2<< endl;
    cout << set3 << endl;

    set3 = set + set2;
    cout << set3 << endl;

    cout << "difference" << endl;
    cout << set << endl;
    cout << set2 << endl;
    set.insert(4);
    set.insert(4);
    set.insert(9);
    set2 = set2 - set;
    cout << set2 << endl;
    return 0;
}

