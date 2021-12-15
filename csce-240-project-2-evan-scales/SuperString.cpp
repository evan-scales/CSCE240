// Copyright 2021 <Enter Name Here>
#include "./SuperString.h"

// DO NOT MODIFY START
void SuperString::print() {
    if (size != 0) {
        for (int i = 0; i < size; i++) {
            std::cout << data[i];
        }
        std::cout << "\n";
    } else {
        std::cout << "<EMPTY>\n";
    }
}

char SuperString::get(int index) {
    if (index >= 0 && index < size) {
        return data[index];
    }
    return '\0';
}

int SuperString::length() {
    return size;
}
// DO NOT MODIFY END

// PUT YOUR CODE BELOW!

SuperString::SuperString() {
    size = 0;
    data = new char[size];
}

SuperString::SuperString(std::string str) {
    size = str.length();
    data = new char[size];
    for (int i = 0; i < size; i++)
        data[i] = str[i];
}

SuperString::SuperString(int size, char val) {
    this->size = size;
    data = new char[size];
    for (int i = 0; i < size; i++)
        data[i] = val;
}

SuperString::SuperString(const SuperString& copy) {
    size = copy.size;
    data = new char[size];
    for (int i = 0; i < size; i++)
        data[i] = copy.data[i];
}

int SuperString::find(char c, int start) {
    for (int i = start; i < size; i++) {
        if (data[i] == c)
            return i;
    }
    return -1;
}

int SuperString::find(std::string str, int start) {
    int strSize = str.length();
    for (int i = start; i < size; i++) {
        // First 2 indexes to avoid having to go
        // through all this if its like a space that matches
        if (data[i] == str[0] && data[i+1] == str[1]) {
            int count = 0;
            for (int j = 0; j < strSize; j++) {
                if (data[i+j] == str[j])
                    count++;
                else
                    break;
            }
            if (count == strSize)
                return i;
        }
    }
    return -1;
}

SuperString SuperString::substr(int start, int numChar) {
    std::string ret = "";
    if ((start >= 0 && start < size - 1) && (numChar < size - 1)) {
        for (int i = start; i < numChar; i++)
            ret += data[i];
    }
    return SuperString(ret);
}

SuperString SuperString::reverse() {
    std::string ret = "";
    for (int i = size-1; i > -1; i--)
        ret += data[i];
    return SuperString(ret);
}

SuperString SuperString::replace(int start, int numChar, std::string sub) {
    std::string ret = "";
    // First determine if sub will be placed between two string,
    //  at the start, or at the end
    if ((start >= 0 && start < size) && (numChar < size - 1)) {
        if (start == 0) {
            // Find substring after numChar, add sub to that
            std::string sub1 = "";
            for (int i = numChar; i < size; i++)
                sub1 += data[i];
            ret = sub + sub1;
        } else if (start == size - 1) {
            std::string sub1 = "";
            for (int i = 0; i < start; i++)
            sub1 += data[i];
            ret = sub1 + sub;
        } else {
            std::string sub1, sub2 = "";
            // First subString
            for (int i = 0; i < start; i++)
                sub1 += data[i];
            // Second substring
            for (int i = start + numChar; i < size - 1; i++)
                sub2 += data[i];
            ret = sub1 + sub + sub2;
        }
    }
    return SuperString(ret);
}

void SuperString::push_back(char c) {
    char *temp = data;
    data = new char[size + 1];
    for (int i = 0; i < size; i++)
        data[i] = temp[i];
    data[size] = c;
    size++;
    delete [] temp;
}

void SuperString::append(std::string str) {
    char *temp = data;
    data = new char[size + str.length()];
    for (int i = 0; i < size; i++)
        data[i] = temp[i];
    for (int i = size; i < size + str.length(); i++)
        data[i] = str[i - size];
    size += str.length();
    delete [] temp;
}

void SuperString::append(const SuperString& obj) {
    char *temp = data;
    data = new char[size + obj.size];
    for (int i = 0; i < size; i++)
        data[i] = temp[i];
    for (int i = size; i < size + obj.size; i++)
        data[i] = obj.data[i - size];
    size += obj.size;
    delete [] temp;
}

void SuperString::replace(char find, char rep) {
    for (int i = 0; i < size; i++) {
        if (data[i] == find)
            data[i] = rep;
    }
}

void SuperString::removeAll(char c) {
    int newSize = size;
    for (int i = 0; i < size; i++) {
        if (data[i] == c)
            newSize--;
    }
    std::string build = "";
    for (int i = 0; i < size; i++) {
        if (data[i] != c)
            build += data[i];
    }
    delete [] data;
    data = new char[newSize];
    for (int i = 0; i < newSize; i++)
        data[i] = build[i];
    size = newSize;
}

// Bonus Methods
void SuperString::replace(std::string find, std::string rep) {
    int found = 0;
    // Array to hold the starting index of the substring to replace
    // Won't work if replacing more than 20 sub strings
    int foundSize = 20;
    int indexes[20];
    // Kept getting cpplint error when doing
    // int indexes[foundSize];
    for (int i = 0; i < foundSize; i++)  // Assign all indexs -1
        indexes[i] = -1;
    int findSize = find.length();
    for (int i = 0; i < size; i++) {
        // Find instances of find
        if (data[i] == find[0] && data[i+1] == find[1]) {
            int count = 0;
            for (int j = 0; j < findSize; j++) {
                if (data[i+j] == find[j])
                    count++;
                else
                    break;
            }
            // Found index of find
            if (count == findSize) {
                indexes[found] = i;
                found++;
            }
        }
    }
    // Repalce
    for (int i = 0; i < foundSize; i++) {
        int start = indexes[i];
        if (start != -1) {
            for (int j = start; j < start + findSize; j++)
                data[j] = rep[j - start];
        } else {
            break;
        }
    }
}

bool SuperString::isUpper() {
    for (int i = 0; i < size; i++) {
        if (islower(data[i]))
            return false;
    }
    return true;
}

bool SuperString::isLower() {
    for (int i = 0; i < size; i++) {
        if (isupper(data[i]))
            return false;
    }
    return true;
}

bool SuperString::isTitleCase() {
    int length = 0;
    for (int i = 0; i < size; i++) {
        length++;
        if (data[i] == 32 || i == size - 1) {
            length--;
            if (islower(data[i - length]))
                return false;
            length = 0;
        }
    }
    return true;
}

SuperString::~SuperString() {
    delete [] data;
}
