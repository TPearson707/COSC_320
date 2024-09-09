/*
 * Name of Author: Thomas Pearson
 * Date of Creation: 2/22/2024
 * Date of Last Update: 2/22/2024
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

// Counting functions
template <class T> int count (T* begin, T* end, const T& val, comparisonPtr<T> fctPtr);
template <class T> int count (typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, comparisonPtr<T> fctPtr);


template <class T> void alter(T* begin, T* end, const T& val, strPtr<T> fctPtr);
template <class T> void alter(typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, strPtr<T> fctPtr);

template <class T> bool Greater(const T& one, const T& two);
template <class T> bool Equal(const T& one, const T& two);
template <class T> bool Less(const T& one, const T& two);

string ucase(string str);
string lcase(string str);

void ucaseref(string& str);
void lcaseref(string& str);

string substrto(string str1, string str2);
bool hassubstr(const string& str1, const string& str2);
bool startswith(const string& str1, const string& str2);
bool endswith(const string& str1, const string& str2);

int main () {
    string filename;
    vector<string> data;
    cout << "Please enter the dictionary name: ";
    cin >> filename;
    cout << endl;

    ifstream myfile;

    myfile.open(filename);

    if (myfile.is_open()) {
        string current;
        while (!myfile.eof()) {
            getline(myfile, current);
            current = substrto(current, "/");
            data.push_back(current);
        }
    } else {
        cout << "file could not be opened" << endl;
        exit(1);
    }

    myfile.close();

    alter(data.begin(), data.end(), *data.begin(), ucaseref);

    const string THE = "THE";
    cout << "Number of THE substrings: " << count(data.begin(), data.end(), THE, hassubstr) << endl;
    const string ER = "ER";
    cout << "Number of words that end in ER: " << count(data.begin(), data.end(), ER, endswith) << endl;
    cout << "Number of words that starts with THE: " << count(data.begin(), data.end(), THE, startswith) << endl;
    const string T = "T";
    cout << "Number of words that start with T: " << count(data.begin(), data.end(), T, startswith) << endl;

    string alphabetAM = "Q";
    for (int i = 81; i < 86; i++) {
        cout << "Number of words that start with " << alphabetAM[0] << " " << count(data.begin(), data.end(), alphabetAM, startswith) << endl;
        char temp = alphabetAM[0];
        temp++;
        alphabetAM[0] = temp;
    }

    alphabetAM = "A";
    for (int i = 65; i < 78; i++) {
        cout << "Number of words that start with " << alphabetAM[0] << " " << count(data.begin(), data.end(), alphabetAM, startswith) << endl;
        char temp = alphabetAM[0];
        temp++;
        alphabetAM[0] = temp;
    }

    return 0;
}

/*
 * Description: counting function that takes in a begin and end point loops through the array and adds 1 to counter if evaluating function at use returns true.
 * Parameters: T* begin, T* end, const T& val, functPtr<T> fctPtr
 * Return Type: int
 */
template <class T> int count (T* begin, T* end, const T& val, comparisonPtr<T> fctPtr) {
    int counter = 0;

    for (int* i = begin; i < end; i++) {
        if (fctPtr(*i, val))
            counter++;
    }

    return counter;
}

/*
 * Description: same as the previous counting function, but uses iterators from the vector library
 * Parameters: typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, functPtr<T> fctPtr
 * Return Type: int
 */
template <class T> int count (typename vector<T>::iterator begin, typename vector<T>::iterator end, const T& val, comparisonPtr<T> fctPtr) {
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
 * Description: Comparison function to compare two values. If one > two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Greater(const T& one, const T& two) {
    return one > two;
}


/*
 * Description: Comparison function to compare two values. If one == two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Equal(const T& one, const T& two) {
    return one == two;
}

/*
 * Description: Comparison function to compare two values. If one < two returns true if not returns false;
 * Parameters: const T& one, const T& two
 * Return Type: bool
 */
template <class T> bool Less(const T& one, const T& two) {
    return one < two;
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

    if (hassubstr) {
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

