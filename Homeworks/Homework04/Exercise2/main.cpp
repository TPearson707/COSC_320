/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 2/27/2024
 * Date of Last Update: 2/27/2024
 */


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Function Pointers
template <class T> using comparisonPtr = bool(*)(const T& one, const T& two);
template <class T> using strPtr = void (*)(T& one);

template <class T, class P, class FCT> long count(P, P, const T &, FCT);

template <class T> void alter(T* begin, T* end, const T& val, strPtr<T> fctPtr);
template <class T> void alter(typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, strPtr<T> fctPtr);

template <class T> bool GreaterEqual(T one, T two);

string ucase(string str);
string lcase(string str);

void ucaseref(string& str);
void lcaseref(string& str);

string substrto(string str1, string str2);
bool hassubstr(const string& str1, const string& str2);
bool startswith(const string& str1, const string& str2);
bool endswith(const string& str1, const string& str2);

int main () {

//     auto Greater = [](const auto one, const auto two) {return one > two;};
//     auto Equal = [](const auto one, const auto two) {return one == two;};
//     auto Less = [](const auto one, const auto two) {return one < two;};

    int arr1[7] = {2, 5, 6, 9, 10, 1, 1};
    double arr2[7] = {4, 4, 2, 9, 0, 3, 4};
    vector<int> vec1 = {2, 5, 6, 9, 10, 1, 1};
    vector<double> vec2 = {4, 4, 2, 9, 0, 3, 4};

    auto Greater = [](auto one, auto two) -> bool {
        return one > two;
    };

    auto Equal = [](auto one, auto two) -> bool {
        return one == two;
    };

    auto Less = [](auto one, auto two) -> bool {
        return one < two;
    };

    cout << count(arr1, arr1 + 7, 3, Greater) << endl;
    cout << count(arr1, arr1 + 7, 3, Equal) << endl;
    cout << count(arr1, arr1 + 7, 3, Less) << endl;
    cout << count(arr1, arr1 + 7, 3, GreaterEqual<int>) << endl;

    cout << endl;

    cout << count(arr2, arr2 + 7, 3.0, Greater) << endl;
    cout << count(arr2, arr2 + 7, 3.0, Equal) << endl;
    cout << count(arr2, arr2 + 7, 3.0, Less) << endl;
    cout << count(arr2, arr2 + 7, 3.0, GreaterEqual<double>) << endl;

    cout << endl;

    cout << count(vec1.begin(), vec1.end(), 3, Greater) << endl;
    cout << count(vec1.begin(), vec1.end(), 3, Equal) << endl;
    cout << count(vec1.begin(), vec1.end(), 3, Less) << endl;
    cout << count(vec1.begin(), vec1.end(), 3, GreaterEqual<int>) << endl;

    cout << endl;

    cout << count(vec2.begin(), vec2.end(), 3.0, Greater) << endl;
    cout << count(vec2.begin(), vec2.end(), 3.0, Equal) << endl;
    cout << count(vec2.begin(), vec2.end(), 3.0, Less) << endl;
    cout << count(vec2.begin(), vec2.end(), 3.0, GreaterEqual<double>) << endl;

    cout << endl;

    cout << count(arr1, arr1 + 7, 3, [](auto one, auto two) -> bool {return one <= two;}) << endl;
    cout << count(arr2, arr2 + 7, 3.0, [](auto one, auto two) -> bool {return one <= two;}) << endl;
    cout << count(vec1.begin(), vec1.end(), 3, [](auto one, auto two) -> bool {return one <= two;}) << endl;
    cout << count (vec2.begin(), vec2.end(), 3.0, [](auto one, auto two) -> bool {return one <= two;}) << endl;

    return 0;
}

/*
 * Description: counting function that takes in a begin and end point loops through the array and adds 1 to counter if evaluating function at use returns true.
 * Parameters: P begin, P end, const T & val, FCT fctPtr
 * Return Type: long
 */
template <class T, class P, class FCT> long count(P begin, P end, const T & val, FCT fctPtr) {
    int counter = 0;

    for (begin = begin; begin < end; begin++) {
        if (fctPtr(*begin, val))
            counter++;
    }

    return counter;
}

template <class T> void alter(T* begin, T* end, const T& val, strPtr<T> fctPtr) {
    for_each (begin, end, fctPtr);
}

template <class T> void alter(typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, strPtr<T> fctPtr) {
    for_each (begin, end, fctPtr);
}

/*
 * Description: Comparison function to compare two values. If one >= two returns true if not returns false;
 * Parameters: T one, T two;
 * Return Type: bool
 */
template <class T> bool GreaterEqual(T one, T two) {
    return one >= two;
}

/*
 * Description: takes a string by value and converts to uppercase returns string
 * Parameters: string str
 * Return Type: string
 */
string ucase(string str) {

    for (size_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

/*
 * Description: take a string by value and converts to lowercase
 * Parameters: string str
 * Return Type: string
 */
string lcase(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

/*
 * Description: take a string by reference and converts to uppercase
 * Parameters: string& str
 * Return Type: string
 */
void ucaseref(string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
}

/*
 * Description: take a string by reference and converts to lowercase
 * Parameters: string& str
 * Return Type: string
 */
void lcaseref(string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
}

/*
 * Description: takes 2 strings by value, checks if string 2 is a substring of string 1 if true returns string 1 before substring if false returns string 1
 * Parameters: string str1 string str2
 * Return Type: string
 */
string substrto(string str1, string str2) {

    if (hassubstr(str1, str2)) {
        size_t pos = str1.find(str2);
        string str3 = str1.substr(0, pos);
        return str3;
    } else {
        return str1;
    }
}

/*
 * Description: takes 2 strings by constant reference, and checks to see if string 1 has a substring of string 2
 * Parameters: const string& str1, const string& str2
 * Return Type: bool
 */
bool hassubstr(const string& str1, const string& str2) {
    try {
        size_t pos = str1.find(str2);
        string str3 = str1.substr(pos, str2.length());
        return str3 == str2;
    } catch (exception e) {
        return false;
    }

    return false;
}

/*
 * Description: takes 2 strings by constant reference, and checks to see if string 1 starts with string 2
 * Parameters: const string& str1, const string& str2
 * Return Type: bool
 */
bool startswith(const string& str1, const string& str2) {
    size_t pos = str2.length();
    string str3 = str1.substr(0, pos);

    return str3 == str2;
}

/*
 * Description: takes 2 strings by constant reference, and checks to see if string 1 ends with string 2
 * Parameters: const string& str1, const string& str2
 * Return Type: bool
 */
bool endswith(const string& str1, const string& str2) {
    size_t pos = str2.length();

    if (pos > str1.length())
        return false;

    string str3 = str1.substr(str1.length() - pos);

    return str3 == str2;
}
