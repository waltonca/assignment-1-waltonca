//
// Created by Walton Zhang on 2024-09-27.
//
#include "LinkedList.h"

// Add one line to the chain
void LinkedList::addLine(const std::string &line) {
    auto new_node = new LinkedListNode({._data=line});
    if (_start == nullptr) {
        _start = new_node;
    } else {
        LinkedListNode *node = _start;
        while (node->_next != nullptr) {
            node = node->_next;
        }
        node->_next = new_node;
    }
}

// Inserts text to the specified line
void LinkedList::insertLine(int index, const std::string &line) {
    auto new_node = new LinkedListNode({._data=line});

    if (index == 0) { // Insert into the first line
        new_node->_next = _start;
        _start = new_node;
    } else {
        LinkedListNode *node = _start;
        int curr_idx = 0;

        // Finds the node before the specified line
        while (node != nullptr && curr_idx < index - 1) {
            node = node->_next;
            curr_idx++;
        }

        if (node != nullptr) {
            new_node->_next = node->_next;
            node->_next = new_node;
        } else {
            std::cout << "Line " << index << " not found!" << std::endl;
        }
    }
}

// Print all the lines
void LinkedList::printLines() const {
    LinkedListNode *node = _start;
    int line_num = 1;
    while (node != nullptr) {
        std::cout << line_num++ << "> " << node->_data << std::endl;
        node = node->_next;
    }
}

// Print specified line
void LinkedList::printLine(int index) const {
    LinkedListNode *node = _start;
    int curr_idx = 0;

    while (node != nullptr && curr_idx < index) {
        node = node->_next;
        curr_idx++;
    }

    if (node != nullptr) {
        std::cout << curr_idx + 1 << "> " << node->_data << std::endl;
    } else {
        std::cout << "Line " << index + 1 << " not found!" << std::endl;
    }
}

// Print range of lines
void LinkedList::printRange(int start, int end) const {
    LinkedListNode *node = _start;
    int curr_idx = 0;

    while (node != nullptr && curr_idx < start) {
        node = node->_next;
        curr_idx++;
    }

    while (node != nullptr && curr_idx <= end) {
        std::cout << curr_idx + 1 << "> " << node->_data << std::endl;
        node = node->_next;
        curr_idx++;
    }

    if (curr_idx <= end) {
        std::cout << "Range [" << start + 1 << ", " << end + 1 << "] exceeds file content!" << std::endl;
    }
}

// Save content to file
void LinkedList::saveToFile(const std::string &filename) const {
    std::ofstream outFile(filename);
    LinkedListNode *node = _start;
    while (node != nullptr) {
        outFile << node->_data << std::endl;
        node = node->_next;
    }
    outFile.close();
}

// Load content from file
void LinkedList::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) { // if file exists, load it
        std::string line;
        while (std::getline(inFile, line)) {
            addLine(line);
        }
        inFile.close();
    }
}

// Get current line count
int LinkedList::getLineCount() const {
    int count = 0;
    LinkedListNode *node = _start;
    while (node != nullptr) {
        count++;
        node = node->_next;
    }
    return count;
}

// Delete a specific line
void LinkedList::deleteLine(int index) {
    LinkedListNode *node = _start;
    LinkedListNode *prev = nullptr;
    int curr_idx = 0;

    while (node != nullptr && curr_idx < index) {
        prev = node;
        node = node->_next;
        curr_idx++;
    }

    if (node != nullptr) {
        if (prev == nullptr) {
            _start = node->_next; // delete first line
        } else {
            prev->_next = node->_next; // delete middle line
        }
        delete node;
    } else {
        std::cout << "Line " << index + 1 << " not found!" << std::endl;
    }
}

// Delete a range of lines
void LinkedList::deleteRange(int start, int end) {
    for (int i = start; i <= end; ++i) {
        deleteLine(start);
    }
}