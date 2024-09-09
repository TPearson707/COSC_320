#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <class T> class Heap {
  private:
    vector<T> data;

  public:
    Heap(){};
    Heap(vector<T>);
    Heap(T[], int);

    void insert(T);
    T dequeue();
    bool empty();
    void clear() { data.clear(); };
    void setData(vector<T>);
    void setData(T[], int);
    void append(vector<T>);
    void append(T[], int);

    static void sort(vector<T> &);
    static void sort(T[], int);

    template <class U>
    friend ostream &operator<<(ostream &strm, const Heap<U> &obj);
};

template <class T> Heap<T>::Heap(vector<T> v) {
    data = v;
    make_heap(data.begin(), data.end());
}

template <class T> Heap<T>::Heap(T A[], int s) {
    data.insert(data.end(), A, A + s);
    make_heap(data.begin(), data.end());
}

template <class T> void Heap<T>::setData(vector<T> v) {
    data = v;
    make_heap(data.begin(), data.end());
}

template <class T> void Heap<T>::setData(T A[], int s) {
    data.clear();
    data.insert(data.end(), A, A + s);
    make_heap(data.begin(), data.end());
}

template <class T> void Heap<T>::append(vector<T> v) {
    data.insert(data.end(), v.begin(), v.end());
    make_heap(data.begin(), data.end());
}

template <class T> void Heap<T>::append(T A[], int s) {
    data.insert(data.end(), A, A + s);
    make_heap(data.begin(), data.end());
}

template <class T> void Heap<T>::insert(T item) {
    data.push_back(item);
    push_heap(data.begin(), data.end());
}

template <class T> T Heap<T>::dequeue() {
    pop_heap(data.begin(), data.end());
    T retitem = data.back();
    data.pop_back();
    return retitem;
}

template <class T> bool Heap<T>::empty() { return data.empty(); }

template <class T> void Heap<T>::sort(vector<T> &v) {
    make_heap(v.begin(), v.end());
    sort_heap(v.begin(), v.end());
}

template <class T> void Heap<T>::sort(T A[], int s) {
    make_heap(A, A + s);
    sort_heap(A, A + s);
}

template <class U> ostream &operator<<(ostream &strm, const Heap<U> &obj) {
    if (!obj.data.empty()) {
        strm << "[";
        for (unsigned long i = 0; i < obj.data.size(); i++)
            if (i < obj.data.size() - 1)
                strm << obj.data[i] << ", ";
            else
                strm << obj.data[i] << "]";
    }

    return strm;
}
