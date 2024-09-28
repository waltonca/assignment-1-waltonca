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

    // Print specified line
    void printLine(int index) const {
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
    void printRange(int start, int end) const {
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

    // delete special line
    void deleteLine(int index) {
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

    // delete range for lines
    void deleteRange(int start, int end) {
        for (int i = start; i <= end; ++i) {
            deleteLine(start);
        }
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
            editor.saveToFile(filename); // E - exit with save
            break;
        } else if (command == "Q") {
            std::cout << "Exiting without saving." << std::endl;
            break; // Q - exit without save
        } else if (command[0] == 'D') {
            // 3 types
            // D 1
            // D 1 3
            // D
            std::stringstream ss(command);
            char D;
            int num1, num2;
            ss >> D;

            if (ss >> num1) { // get num1
                if (ss >> num2) { // get num2
                    editor.deleteRange(num1 - 1, num2 - 1); // delete range frm num1 to num2
                    line_num = std::min(line_num, editor.getLineCount() + 1); // update line number
                } else { // if no num2, which means have only one number
                    editor.deleteLine(num1 - 1); // delete num1 line
                    line_num = std::min(line_num, editor.getLineCount() + 1); // update line number
                }
            } else { //  no num1, num2.
                editor.deleteLine(line_num - 2); // delete previous line
                line_num = std::min(line_num - 1, editor.getLineCount() + 1); // update line number
            }

        } else if (command[0] == 'L') {
            std::stringstream ss(command);
            char L;
            int num1, num2;
            ss >> L;

            if (ss >> num1) { // get num1
                if (ss >> num2) { // get num2
                    editor.printRange(num1 - 1, num2 - 1); // display range frm num1 to num2
                    line_num = num2 + 1; //  current line will be changed to the next line.
                } else { // only num1
                    editor.printLine(num1 - 1); // display this line
                    line_num = num1 + 1; // current line will be changed to the line following that line
                }
            } else { // no num1, num2
                editor.printLines(); //  entire contents of the linked list is displayed
            }
        } else if (!command.empty()) {
            editor.addLine(command); // add new line
            line_num++;
        }
    }

    return 0;
}