// Copyright 2021 Evan Scales
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using std::vector;
using std::cout;
using std::string;


void readPuzzle(vector<vector<char> > &puzzle, string filename);
void readWords(vector<string> &words, string filename);
void printPuzzle(const vector<vector<char> > &puzzle);
void printWords(const vector<string> &words);
void printLocation(string word, const vector<int> &start,
                   const vector<int> &end, bool found);
bool findWord(const vector<vector<char> > & puzzle, string word,
              vector<int> &start, vector<int> &end);

int main(int argc, char **argv) {
  string puzzleFileName;
  string wordsFileName;
  vector<vector<char> > puzzle;
  vector<string> words;
  if (argc != 3) {
    cout << "Usage: ./sub2 puzzle.txt words.txt\n";
    exit(0);
  }
  puzzleFileName = argv[1];
  wordsFileName = argv[2];
  readPuzzle(puzzle, puzzleFileName);
  readWords(words, wordsFileName);
  printPuzzle(puzzle);
  printWords(words);

  for (auto word : words) {
    vector<int> start;
    vector<int> end;
    bool found;
    found = findWord(puzzle, word, start, end);
    printLocation(word, start, end, found);
    end.clear();
    start.clear();
  }
  return 0;
}

void readPuzzle(vector<vector<char> > &puzzle, string filename) {
    std::ifstream in(filename);
    int i = 0;
    std::string line, token = "";
    if (in.is_open()) {
      while (getline(in, line)) {
        std::vector<char> row;
        puzzle.push_back(row);
        for (int k = 0; k < line.length(); k++) {
          char c = line[k];
          if (c != 32)
            puzzle[i].push_back(c);
        }
        i++;
      }
      
    } else {
      std::cout << "No file\n";
    }
    return;
}

void readWords(vector<string> &words, string filename) {
    std::ifstream in(filename);
    std::string line = "";
    if (in.is_open()) {
      while (getline(in, line))
        words.push_back(line);
    } else {
      std::cout << "No file\n";
    }
}

void printPuzzle(const vector<vector<char> > &puzzle) {
    for (auto vect : puzzle) {
      for (char c : vect)
        std::cout << c << "  ";
      std::cout << "\n";
    }
}

void printWords(const vector<string> &words) {
    for (std::string word : words)
      std::cout << word << "\n";
}

void printLocation(string word, const vector<int> &start,
                   const vector<int> &end, bool found) {
    if (found) {
      std::cout << "Word " << word << " found at (" << start[0] << ", " << start[1] << ") -> (" << end[0] << ", " << end[1] << ")\n";
    } else {
      std::cout << "Word " << word << " not found\n";
    }
}

bool findWord(const vector<vector<char>> & puzzle, string word,
              vector<int> &start, vector<int> &end) {
    for (int i = 0; i < puzzle.size(); i++) {
      for (int j = 0; j < puzzle[i].size(); j++) {
        if (puzzle[i][j] == word[0]) {
          // std::cout << puzzle[i][j];
          start.push_back(i);
          start.push_back(j);
          // Search left
          for (int k = 0; k < word.size(); k++) {
            if ((j - k) >= 0) {
              if (puzzle[i][j-k] != word[k]) {
                break;
              }
              else if (k == word.size() - 1) {
                end.push_back(i);
                end.push_back(j-k);
                return true;
              }
            } else {
              break;
            }
          }
          // Search right
          for (int k = 0; k < word.size(); k++) {
            if ((j + k) < puzzle[i].size()) {
              if (puzzle[i][j+k] != word[k]) {
                break;
              }
              else if (k == word.size() - 1) {
                end.push_back(i);
                end.push_back(j+k);
                return true;
              }
            } else {
              break;
            }
          }
          // Search up
          for (int k = 0; k < word.size(); k++) {
            if ((i - k) >= 0) {
              if (puzzle[i-k][j] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i-k);
                end.push_back(j);
                return true;
              }
            } else {
              break;
            }
          }
          // Search down
          for (int k = 0; k < word.size(); k++) {
            if ((i + k) < puzzle.size()) {
              if (puzzle[i+k][j] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i+k);
                end.push_back(j);
                return true;
              }
            } else {
              break;
            }
          }
          // Search up left
          for (int k = 0; k < word.size(); k++) {
            if ((i - k) >= 0 && (j - k) >= 0) {
              if (puzzle[i-k][j-k] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i-k);
                end.push_back(j-k);
                return true;
              }
            } else {
              break;
            }
          }
          // Search up right
          for (int k = 0; k < word.size(); k++) {
            if ((i - k) >= 0 && (j + k) < puzzle[i].size()) {
              if (puzzle[i-k][j+k] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i-k);
                end.push_back(j+k);
                return true;
              }
            } else {
              break;
            }
          }
          // Search down left
          for (int k = 0; k < word.size(); k++) {
            if ((i + k) < puzzle.size() && (j - k) >= 0) {
              if (puzzle[i+k][j-k] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i+k);
                end.push_back(j-k);
                return true;
              }
            } else {
              break;
            }
          }
          // Search down right
          for (int k = 0; k < word.size(); k++) {
            if ((i + k) < puzzle.size() && (j + k) < puzzle[i].size()) {
              if (puzzle[i+k][j+k] != word[k]) {
                break;
              } else if (k == word.size() - 1) {
                end.push_back(i+k);
                end.push_back(j+k);
                return true;
              }
            } else {
              break;
            }
          }
          start.clear();
        }
      }
    }
    return false;
}
