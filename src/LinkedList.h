//
// Created by Walton Zhang on 2024-09-27.
//

#ifndef ASSIGNMENT1_SRC_LINKEDLIST_H_
#define ASSIGNMENT1_SRC_LINKEDLIST_H_

#include <iostream>
#include <fstream>
#include <string>

class LinkedList {
private:
  struct LinkedListNode {
    std::string _data;
    LinkedListNode *_next{nullptr};
  };

  LinkedListNode *_start{nullptr};

public:
  void addLine(const std::string &line);
  void insertLine(int index, const std::string &line);
  void printLines() const;
  void printLine(int index) const;
  void printRange(int start, int end) const;
  void saveToFile(const std::string &filename) const;
  void loadFromFile(const std::string &filename);
  int getLineCount() const;
  void deleteLine(int index);
  void deleteRange(int start, int end);
};

#endif //ASSIGNMENT1_SRC_LINKEDLIST_H_
