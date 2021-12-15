// Copyright 2021 Evan Scales
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::cout;
using std::string;

void readData(vector<string> &data, string filename);
void printData(const vector<string> &data);
vector<int> findMinHamming(const vector<string> & data, string test);
void printMinDistance(const vector<string> &data, string word,
                      const vector<int> min);

int main(int argc, char **argv) {
  string filename;
  vector<string> data;
  if (argc != 2) {
    cout << "Usage: ./sub1 data.txt\n";
    exit(0);
  }
  filename = argv[1];
  readData(data, filename);
  printData(data);
  for (auto line : data) {
    vector<int> ret;
    ret = findMinHamming(data, line);
    printMinDistance(data, line, ret);
  }
  return 0;
}

void readData(vector<string> &data, string filename) {
  std::ifstream in(filename);
  std::string line = "";
  if (in.is_open()) {
    while (getline(in, line))
      data.push_back(line);
  } else {
    cout << "NO FILE FOUND\n";
    exit(0);
  }
}

void printData(const vector<string> &data) {
  for (string word : data)
    cout << word << "\n";
}

vector<int> findMinHamming(const vector<string> & data, string test) {
  vector<int> ret; 
  int min = time(NULL);

  for (int i = 0; i < data.size(); i++) {
    // cout << "I: " << i << "\n";
    int minHamming = 0;
    string word = data[i];
    if (word == test)
      continue;
    string *small, *big;
    if (word.size() > test.size()) {
      big = &word;
      small = &test;
    } else {
      big = &test;
      small = &word;
    }
    if (word.size() != test.size())
      minHamming = (big->size() - small->size());
    for (int j = 0; j < small->size(); j++) {
      if ((*small)[j] != (*big)[j])
        minHamming++;
    }
    if (minHamming < min) {
      min = minHamming;
      ret.clear();
      ret.push_back(i);
      ret.push_back(min);
    }
  }
  return ret;
}

void printMinDistance(const vector<string> &data, string word,
                      const vector<int> min) {
  cout << "The minimum hamming distance for " << word << " is " 
  << min[1] << " (matching word: " << data[min[0]] << ")\n";
  return;
}
