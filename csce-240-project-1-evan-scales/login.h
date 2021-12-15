// Author: Evan Scales
// Email: escales@email.sc.edu
// Section #: 002
// Copyright 2021 Evan Scales
// Modified from template code @coleca24 GitHub
#ifndef LOGIN_H_
#define LOGIN_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::cout;
using std::cin;

const int COLS = 4;
const int ROWS = 5;

// TODO(commit 1): Commit #1 functions
void printUsers(const string data[ROWS][COLS]);
bool readUsers(string fh, string data[ROWS][COLS]);
char displayOptions();
bool validateOption(char option);
void executeOption(char option, string data[ROWS][COLS], string file);
int searchForUser(string name, const string data[ROWS][COLS]);

// TODO(commit 2): Commit #2 functions
int findAllUsers(string title, const string data[ROWS][COLS]);
bool deleteUser(string name, string data[ROWS][COLS], string fh);
string generatePassword();
string generateEmail(string name);
int checkEmpty(const string data[ROWS][COLS]);
void addUser(int index, string name, string title,
             string data[ROWS][COLS], string fh);

// Prototypes
bool writeArray(const string data[ROWS][COLS], string file);

// COMMIT 1
void printUsers(const string data[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j == COLS - 1) {
                cout << data[i][j];
            } else {
                cout << data[i][j] << ",";
            }
        }
        cout << "\n";
    }
}
bool readUsers(string fh, string data[ROWS][COLS]) {
    std::ifstream in(fh);
    int i = 0;
    int j = 0;
    string line, token = "";
    if (in.is_open()) {
         while (getline(in, line)) {
            std::stringstream s_line(line);
            while (getline(s_line, token, ',')) {
                    data[i][j] = token;
                    j++;
            }
            i++;
            j = 0;
        }
        return true;
    } else {
        cout << "no file\n";
        return false;
    }
    in.close(); 
}
char displayOptions() {
    cout << "Please Choose one of the following options" << "\n";
    cout << "P(or p): Print data" << "\n";
    cout << "S(or s): Search data by name" << "\n";
    cout << "F(or f): Find all in data with a certain job title" << "\n";
    cout << "A(or a): Add a new user" << "\n";
    cout << "D(or d): Delete an existing user" << "\n";
    cout << "E(or e): End session" << "\n";
    char option;
    cin >> option;
    if (validateOption(option)) {
        return option;
    } else {
        return 'e';
        cout << "Not a valid option, ending session";
    }
}
bool validateOption(char option) {
    if (option == 'E' || option == 'e'|| option == 'P'|| option == 'p'||
     option == 'S'|| option == 's'|| option == 'F'|| option == 'f'
    || option == 'A'|| option == 'a'|| option == 'D'|| option == 'd')
        return true;
    else
        return false;
}
void executeOption(char option, string data[ROWS][COLS], string file) {
    if (option == 'P' || option == 'p') {
        printUsers(data);
    } else if (option == 'S' || option == 's') {
        string fName = "";
        string lName = "";
        cout << "Please enter a first name: ";
        cin >> fName;
        cout << "Please enter a last name: ";
        cin >> lName;
        string name = fName + " " + lName;
        if (searchForUser(name, data) != -1) {
            cout << "User found at index " << searchForUser(name, data) << "\n";
            // Print user data to screen
            for (int j = 0; j < COLS; j++) {
                if (j == COLS - 1)
                    cout << data[searchForUser(name, data)][j];
                else
                    cout << data[searchForUser(name, data)][j] << ",";
            }
            cout << "\n";
        } else {
            cout << "User was not found" << "\n";
        }
    } else if (option == 'F' || option == 'f') {
        string title;
        cout << "Please enter a job title to search for: ";
        cin >> title;
        cout << "There were " << findAllUsers(title, data)
        << " users with job title " << title << "\n";
    } else if (option == 'A' || option == 'a') {
        int index;
        string name, title, fh;
        if (checkEmpty(data) != -1) {
            string fName, lName, name, title = "";
            // Get name
            cout << "Please enter a first name: ";
            cin >> fName;
            cout << "Please enter a kast name: ";
            cin >> lName;
            cout << "Please enter a job title: ";
            cin >> title;
            name = fName + " " + lName;
            addUser(checkEmpty(data), name, title, data, file);
        } else {
            cout << "Data base full (max 5 users)" << "\n";
        }
    } else if (option == 'D' || option == 'd') {
        string fName, lName = "";
        cout << "Please enter a first name: ";
        cin >> fName;
        cout << "Please enter a last name: ";
        cin >> lName;
        string name = fName + " " + lName;
        if (deleteUser(name, data, file)) {
            cout << "User " << name << " deleted." << "\n";
        } else {
            cout << "User not found" << "\n";
        }
    }
}
int searchForUser(string name, const string data[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        if (data[i][0] == name)
            return i;
    }
    return -1;
}

// COMMIT 2
int findAllUsers(string title, const string data[ROWS][COLS]) {
    int found = 0;
    for (int i = 0; i < ROWS; i++) {
        if (data[i][3] == title) {
            found++;
        }
    }
    return found;
}
bool deleteUser(string name, string data[ROWS][COLS], string fh) {
    // Row number of user to delete
    int i = searchForUser(name, data);
    if (searchForUser(name, data) != -1) {
        // Replaces indexw ith null
        for (int j = 0; j < COLS; j++)
            data[i][j] = "NULL";
        return writeArray(data, fh);
    } else {
        return false;
    }
}

string generatePassword() {
    string ret;
    srand(time(NULL));
    int num, uLetter, count = 0;
    bool different = false;

    // Assign random index for needed number and upper case letter in password
    while (!different) {
        num = rand() % 8;
        if (num != uLetter && count != 0) {
            different = true;
        } else {
           uLetter = rand() % 8;
           num = rand() % 8;
        }
        count++;
    }

    for (int i = 0; i < 8; i++) {
        char c;
        if (i == num) {
            c = rand() % 10 + 48;
        } else if (i == uLetter) {
            c = rand() % 26 + 65;
        } else {
            c = rand() % 26 + 97;
        }
        ret += c;
    }
    return ret;
}
string generateEmail(string name) {
    string find = " ";
    std::size_t found = name.find(find);
    name.replace(found, 1, "");
    string email = name + "@email.com";
    return email;
}
int checkEmpty(const string data[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        if (data[i][0] == "NULL")
            return i;
    }
    return -1;
}
bool writeArray(const string data[ROWS][COLS], string file) {
    std::ofstream out(file, std::ofstream::out);
    if (out.is_open()) {
        for (int i = 0; i < ROWS; i++) {
            for (int j=0; j < COLS; j++) {
                if (j == COLS - 1)
                    out << data[i][j];
                else
                    out << data[i][j] << ",";
            }
            out << "\n";
        }
        return true;
    } else {
        cout << "NO FILE FOUND" << "\n";
        return false;
    }
    out.close();
}
void addUser(int index, string name, string title, string
data[ROWS][COLS], string fh) {
    int i = index;
    for (int j = 0; j < COLS; j++) {
        if (j == 0)
            data[i][j] = name;
        if (j == 1)
            data[i][j] = generateEmail(name);
        if (j == 2)
            data[i][j] = generatePassword();
        if (j == 3)
            data[i][j] = title;
    }
    if (writeArray(data, fh))
        cout << "User successfully added" << "\n";
    else
        cout << "Error with adding user" << "\n";
}

#endif  // LOGIN_H_
