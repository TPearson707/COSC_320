/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 2/21/2024
 * Date of Last Update: 2/22/2024
 * Description Templated funcntion pointers and shenanigans
 */


#include <iostream>
#include <vector>

using namespace std;

/*
 * Description: Function pointer to point to functions that compare two values and return true or false
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> using functPtr = bool(*)(const T& one, const T& two);

/*
 * Description: counting function that takes in a begin and end point loops through the array and adds 1 to counter if evaluating function at use returns true.
 * Parameters: T* begin, T* end, const T& val, functPtr<T> fctPtr
 * Return Type: int
 */
template <class T> int count (T* begin, T* end, const T& val, functPtr<T> fctPtr);

/*
 * Description: same as the previous counting function, but uses iterators from the vector library
 * Parameters: typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, functPtr<T> fctPtr
 * Return Type: int
 */
template <class T> int count (typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, functPtr<T> fctPtr);

/*
 * Description: Comparison function to compare two values. If one > two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Greater(const T& one, const T& two);

/*
 * Description: Comparison function to compare two values. If one == two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Equal(const T& one, const T& two);

/*
 * Description: Comparison function to compare two values. If one < two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Less(const T& one, const T& two);

int main () {
    // Arrays for example.
    int arr1[7] = {2, 5, 6, 9, 10, 1, 1};
    int arr2[7] = {4, 4, 2, 9, 0, 3, 4};

    long num = count(arr1, arr1 + 7, 3, Greater);
    cout << num << endl;

    num = count(arr1, arr1 + 7, 1, Equal);
    cout << num << endl;

    num = count(arr2, arr2 + 7, 4, Equal);
    cout << num << endl;

    num = count(arr2, arr2 + 7, 4, Less);
    cout << num << endl;

    // Vectors for example.
    vector<int> vec1 = {2, 5, 6, 9, 10, 1, 1};
    vector<int> vec2 = {4, 4, 2, 9, 0, 3, 4};

    num = count(vec1.begin(), vec1.end(), 1, Equal);
    cout << num << endl;

    num = count(vec2.begin(), vec2.end(), 4, Equal);
    cout << num << endl;

    num = count(vec2.begin(), vec2.end(), 4, Less);
    cout << num << endl;

    num = count(vec2.begin(), vec2.end(), 4, Greater);
    cout << num << endl;

    return 0;
}

template <class T> int count (T* begin, T* end, const T& val, functPtr<T> fctPtr) {
    int counter = 0;

    for (int* i = begin; i < end; i++) {
        if (fctPtr(*i, val))
            counter++;
    }

    return counter;
}

template <class T> int count (typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, functPtr<T> fctPtr) {
    int counter = 0;

    for (begin = begin; begin < end; begin++) {
        if (fctPtr(*begin, val))
            counter++;
    }

    return counter;
}

template <class T> bool Greater(const T& one, const T& two) {
    return one > two;
}

template <class T> bool Equal(const T& one, const T& two) {
    return one == two;
}

template <class T> bool Less(const T& one, const T& two) {
    return one < two;
}
