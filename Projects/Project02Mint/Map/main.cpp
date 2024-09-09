/*
 * Created by: Thomas Pearson
 * Date of Creation: 04/24/2024
 * Date of Last Update: 04/24/2024
 */
#include <iostream>

#include "Map.h"

using namespace std;

int main() {
    Map<int, string> map;

    cout << map.size() << endl;

    if (map.empty())
        cout << "is empty" << endl;
    else
        cout << "is not empty" << endl;

    map.insert(4, "brand");

    cout << map.size() << endl;

    if (map.empty())
        cout << "is empty" << endl;
    else
        cout << "is not empty" << endl;

    map.insert(4, "penis");

    cout << map.size() << endl;

    map.insert(5, "hello");

    cout << map.size() << endl;

    map.clear();

    cout << "Post Clear: " << map.size() << endl;

    if (map.empty())
        cout << "is empty" << endl;
    else
        cout << "is not empty" << endl;

    map.insert(1, "World");

    cout << map.size() << endl;

    if (map.empty())
        cout << "is empty" << endl;
    else
        cout << "is not empty" << endl;

    map.erase(1);

    cout << "Post erase: " << map.size() << endl;

    if (map.empty())
        cout << "is empty" << endl;
    else
        cout << "is not empty" << endl;

    map.insert(5, "world log");

    cout << "found: " << map.find(55) << endl;

    map.clear();

    map.insert(4, "hello world");

    try {

        cout << map.get(5) << endl;
    } catch (out_of_range & e) {
        cout << e.what() << endl;
    }

    Map<int, int> map2;

    map2.insert(2, 5);

    try {

        cout << map2.get(5) << endl;
    } catch (out_of_range & e) {
        cout << e.what() << endl;
    }
    map2.clear();

    Map<int, string> map3;

    map3.insert(4, "hello world");

    bool equal = map == map3;

    cout << "equal: " << equal << endl;

    map.insert(1, "jkjk");
    map.insert(2, "crying");

    cout << map << endl;
    cout << map3 << endl;

    map3 = map;

    cout << map3 << endl;
    return 0;
}
