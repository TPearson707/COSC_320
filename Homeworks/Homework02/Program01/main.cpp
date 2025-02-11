#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

// bubble sort algorithm
template <class T> void bubble(T A[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                T temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

template <class T> void insertion(T A[], int size) {
    for (int i = 0; i < size; i++) {

        int j = 0;
        T val = A[i];

    for (j = i; j > 0 && A[j - 1] > val; j--)
        A[j] = A[j - 1];

    A[j] = val;
    }
}

template <class T> void selection(T A[], int size) {
    int minindex;
    for (int i = 0; i < size; i++) {
        minindex = i;
    for (int j = i; j < size; j++)
        if (A[j] < A[minindex])
        minindex = j;

    T val = A[i];
    A[i] = A[minindex];
    A[minindex] = val;
    }
}

template <class T> void bubble2Sort(T data[], const int n) {
    bool again = true;
    for (int i = 0; i < n-1 && again; i++)
        for (int j = n-1, again = false; j > i; --j)
            if (data[j] < data[j-1]) {
                swap(data[j], data[j-1]);
                again = true;
            }
}

template <class T> void populateArraySorted(T * data1, T * data2, T * data3, T * data4, int size) {
    for (int i = 0; i < size; i++) {
        data1[i] = i + 1;
        data2[i] = data1[i];
        data3[i] = data2[i];
        data4[i] = data3[i];
    }
}

template <class T> void populateArrayReverse(T * data1, T * data2, T * data3, T * data4, int size) {
    for (int i = 0; i < size; i++) {
        data1[i] = size - i;
        data2[i] = data1[i];
        data3[i] = data2[i];
        data4[i] = data3[i];
    }
}

template <class T> void populateArray(T * data1, T * data2, T * data3, T * data4, int size) {
    for (int i = 0; i < size; i++) {
        data1[i] = rand() % 100 + 1;
        data2[i] = data1[i];
        data3[i] = data2[i];
        data4[i] = data3[i];
    }
}

template <class T> void timeCases(T * data1, T * data2, T * data3, T * data4, int size) {
    // Get start time.
    auto start = high_resolution_clock::now();

    // Do process to be timed.
    bubble(data1, size);

    // Get stop time.
    auto stop = high_resolution_clock::now();

    // Take the difference t get elapsed time.
    auto elapsed = duration_cast<microseconds>(stop - start);

    // Report time.
    cout << "Time to sort using bubble: " << elapsed.count() << " microseconds" << endl;
    cout << "Time to sort using bubble: " << elapsed.count() / 1000000.0 << " seconds" << endl << endl;

    // insertion sort
    start = high_resolution_clock::now();
    insertion(data2, size);
    stop = high_resolution_clock::now();
    elapsed = duration_cast<microseconds>(stop - start);

    cout << "Time to sort using insertion: " << elapsed.count() << " microseconds" << endl;
    cout << "Time to sort insertion: " << elapsed.count() / 1000000.0 << " seconds" << endl << endl;

    // selection sort
    start = high_resolution_clock::now();
    selection(data3, size);
    stop = high_resolution_clock::now();
    elapsed = duration_cast<microseconds>(stop - start);

    cout << "Time to sort using selection: " << elapsed.count() << " microseconds" << endl;
    cout << "Time to sort selection: " << elapsed.count() / 1000000.0 << " seconds" << endl << endl;

    // bubble2 sort
    start = high_resolution_clock::now();
    bubble2Sort(data4, size);
    stop = high_resolution_clock::now();
    elapsed = duration_cast<microseconds>(stop - start);

    cout << "Time to sort using bubble2: " << elapsed.count() << " microseconds" << endl;
    cout << "Time to sort bubble2: " << elapsed.count() / 1000000.0 << " seconds" << endl << endl;
}

int main() {
    int arraySize = 0;
    int numTrials = 4;
    srand(time(0));

    cout << "Enter the size for the arrays: ";
    cin >> arraySize;
    cout << endl;

    int* arrBubble1 = new int[arraySize];
    int* arrInsertion = new int[arraySize];
    int* arrSelection = new int[arraySize];
    int* arrBubble2 = new int[arraySize];

    cout << "Testing Best Cases for each sort" << endl << endl;

    populateArraySorted(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);

    for (int i = 0; i < numTrials; i++) {
        cout << "Trial " << i + 1 << " for best case analysis" << endl << endl;
        timeCases(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);
    }

    cout << "Testing Worst Cases for each sort" << endl << endl;

    for (int i = 0; i < numTrials; i++) {
        cout << "Trial " << i + 1 << " for worst case analysis" << endl << endl;
        populateArrayReverse(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);
        timeCases(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);
    }

    cout << "Testing Average Cases for each sort" << endl << endl;

    for (int i = 0; i < numTrials; i++) {
        cout << "Trial " << i + 1 << " for average case analysis" << endl << endl;
        populateArray(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);
        timeCases(arrBubble1, arrInsertion, arrSelection, arrBubble2, arraySize);
    }



    delete[] arrBubble1;
    delete[] arrInsertion;
    delete[] arrSelection;
    delete[] arrBubble2;

    return 0;
}
