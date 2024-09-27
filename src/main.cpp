#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class LinkedList {
    struct LinkedListNode {
        std::string _data;
        LinkedListNode *_next{nullptr};
    };

    LinkedListNode *_start{nullptr};

public:
    // Add one line to the chain
    void addLine(const std::string& line) {
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

    // Print all the lines
    void printLines() const {
        LinkedListNode *node = _start;
        int line_num = 1;
        while (node != nullptr) {
            std::cout << line_num++ << "> " << node->_data << std::endl;
            node = node->_next;
        }
    }

    // Save content to file
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        LinkedListNode *node = _start;
        while (node != nullptr) {
            outFile << node->_data << std::endl;
            node = node->_next;
        }
        outFile.close();
    }

    // load form file
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (inFile.is_open()) { // if file exit, load it
            std::string line;
            while (std::getline(inFile, line)) {
                addLine(line);
            }
            inFile.close();
        }
        //if file not exit, create a new one
    }

    // get current line
    int getLineCount() const {
        int count = 0;
        LinkedListNode *node = _start;
        while (node != nullptr) {
            count++;
            node = node->_next;
        }
        return count;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: edit <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    LinkedList editor;

    // load file content
    editor.loadFromFile(filename);
    editor.printLines();

    std::string command;
    int line_num = editor.getLineCount() + 1; // start from existing line



    while (true) {
        std::cout << line_num << "> "; // display line number
        std::getline(std::cin, command);

        // Commands
        //
        if (command == "E") {
            editor.saveToFile(filename); // E - exit and save
            break;
        } else if (command.empty()) {
            continue;
        }

        editor.addLine(command); // add new line
        line_num++; // add line number
    }

    return 0;
}