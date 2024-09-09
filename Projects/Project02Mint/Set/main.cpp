/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 04/17/2024
 * Date of Last Update: 04/22/2024
 * Description: Testing program for Set class which is inherited from RBTree.h
*/

#include <iostream>
#include <cstdlib>
#include <vector>

#include "Set.h"

using namespace std;

int main() {
    Set<int> set;

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
    Set<int>set2(set);

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
    Set<int> set3;
    set3 = set + set2;
    set.toVector(vect);
    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << " ";
    cout << endl;
    vect.clear();
    set3.toVector(vect);
    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << " ";
    cout << endl;

    set2 = set3 * set;

    vect.clear();
    set2.toVector(vect);
    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << " ";
    cout << endl;

    set.clear();
    set3.clear();
    set2.clear();

    set.insert(8);
    set.insert(2);
    set.insert(3);
    cout << set << endl;
    set3.insert(8);
    set3.insert(3);
    cout << set << endl;
    set2 = set - set3;
    cout << set << endl;
    vect.clear();
    set2.toVector(vect);

    for (int i = 0; i < vect.size(); i++)
        cout << vect[i] << " ";
    cout << endl;

    cout << set2 << endl;
    cout << set << endl;
    return 0;
}
