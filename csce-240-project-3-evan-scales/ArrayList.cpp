// Copyright 2021 Evan Scales
#include "./ArrayList.h"

template <class U>
ostream& operator<<(ostream & os, ArrayList<U> a) {
    os << "[";
    for (int i = 0; i < a.getSize(); i++) {
        os << a.getData(i) << " ";
    }
    os << "]";
    return os;
}

template <class T>
ArrayList<T>::ArrayList() {
    size = 0;
    data = new T[size];
}

template <class T>
ArrayList<T>::ArrayList(int size, T val) {
    this->size = size;
    data = new T[size];
    for (int i = 0; i <size; i++) {
        data[i] = val;
    }
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T> & copy) {
    setSize(copy.getSize());
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = copy[i];
    }
}

template <class T>
ArrayList<T>::~ArrayList() {
    delete [] data;
}

template <class T>
void ArrayList<T>::setSize(int size) {
    if (size >= 0) {
        this->size = size;
    } else {
        std::cout << "Incorrect size\n";
        exit(1);
    }
}

template <class T>
int ArrayList<T>::getSize() const {
    return size;
}

template <class T>
T ArrayList<T>::getData(int index) const {
    if (index >= 0 && index < size) {
        return data[index];
    } else {
        std::cout << "Invalid Index\n";
        exit(0);
    }
}

template <class T>
T ArrayList<T>::operator[](int index) const {
    if (index >= 0 && index < size) {
        return data[index];
    } else {
        std::cout << "Invalid Index\n";
        exit(0);
    }
}

template <class T>
T& ArrayList<T>::operator[](int index) {
    return data[index];
}

template <class T>
const ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T> rhs) {
    size = rhs.getSize();
    delete [] data;
    data = new T[size];
    for (int i = 0; i < size; i++) {
        data[i] = rhs[i];
    }
    return *this;
}

template <class T>
void ArrayList<T>::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

// Start of new functions

template <class T>
bool ArrayList<T>::operator!=(const ArrayList<T> & rhs) const {
    // First see if size is the same
    if (size != rhs.getSize()) {
        return true;
    } else {
        for (int i = 0; i < size; i++) {
            if (data[i] != rhs[i])
                return true;
        }
    }
    return false;
}

template <class T>
ArrayList<T> ArrayList<T>::operator+(T val) const {
    ArrayList<T> ret(size);
    for (int i = 0; i < size; i ++) {
        ret.data[i] = data[i] + val;
    }
    return ret;
}

template <class T>
ArrayList<T> ArrayList<T>::operator+(const ArrayList<T> & rhs) const {
    ArrayList<T> ret(size);
    if (rhs.getSize() == size) {
        for (int i = 0; i < size; i++)
            ret[i] = data[i] + rhs[i];
    }
    return ret;
}

template <class T>
ArrayList<T> & ArrayList<T>::operator--() {
    T *temp = data;
    data = new T[size-1];
    for (int i = 0; i < size - 1; i++) {
        data[i] = temp[i];
    }
    size--;
    delete [] temp;
    return *this;
}

template <class T>
ArrayList<T> ArrayList<T>::operator--(int) {
    ArrayList<T> ret(*this);
    T *temp = data;
    data = new T[size-1];
    for (int i = 0; i < size - 1; i++) {
        data[i] = temp[i];
    }
    size--;
    delete [] temp;
    return ret;
}

template <class T>
void ArrayList<T>::operator+=(T val) {
    T *temp = data;
    data = new T[size+1];
    for (int i = 0; i < size; i++)
        data[i] = temp[i];
    data[size] = val;
    size++;
    delete [] temp;
}

template <class T>
void ArrayList<T>::operator+=(const ArrayList<T> & rhs) {
    T *temp = data;
    data = new T[size+rhs.getSize()];
    for (int i = 0; i < size; i++)
        data[i] = temp[i];
    for (int i = size; i < size + rhs.getSize(); i++)
        data[i] = rhs[i-size];
    size+= rhs.getSize();
    delete [] temp;
}

template <class T>
ArrayList<T> ArrayList<T>::operator*(int val) const {
    ArrayList<T> ret(size * val);
    for (int i = 0; i < ret.getSize(); i+= val) {
        for (int j = 0; j < size; j++)
           ret[i+j] = data[j];
    }
    return ret;
}

template <class T>
ArrayList<T> ArrayList<T>::operator/(int val) const {
    ArrayList<T> ret(size/val);
    for (int i = 0; i < ret.getSize(); i++)
        ret[i] = data[i];
    return ret;
}
