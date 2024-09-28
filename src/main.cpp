#include <iostream>
#include <sstream>
#include "LinkedList.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: edit <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    LinkedList editor;

    // Load file content
    editor.loadFromFile(filename);
    editor.printLines();

    std::string command;
    int line_num = editor.getLineCount() + 1; // start from existing line

    while (true) {
        std::cout << line_num << "> "; // display line number
        std::getline(std::cin, command);
        std::cout << "Received command: " << command << std::endl; // Debugging line

        // Command processing
        if (command == "E") {
            std::cout << "Saving and exiting..." << std::endl; // Debugging line
            editor.saveToFile(filename);
            break;
        } else if (command == "Q") {
            std::cout << "Exiting without saving." << std::endl; // Debugging line
            break;
        } else if (command[0] == 'D') {
            std::cout << "Delete command triggered." << std::endl; // Debugging line
            std::stringstream ss(command);
            char D;
            int num1, num2;
            ss >> D;

            if (ss >> num1) { // get num1
                if (ss >> num2) { // get num2
                    editor.deleteRange(num1 - 1, num2 - 1); // delete range from num1 to num2
                    line_num = std::min(line_num, editor.getLineCount() + 1); // update line number
                } else { // if no num2
                    editor.deleteLine(num1 - 1); // delete num1 line
                    line_num = std::min(line_num, editor.getLineCount() + 1); // update line number
                }
            } else { // no num1
                editor.deleteLine(line_num - 2); // delete previous line
                line_num = std::min(line_num - 1, editor.getLineCount() + 1); // update line number
            }
        } else if (command[0] == 'L') {
            std::cout << "List command triggered." << std::endl; // Debugging line
            std::stringstream ss(command);
            char L;
            int num1, num2;
            ss >> L;

            if (ss >> num1) { // get num1
                if (ss >> num2) { // get num2
                    editor.printRange(num1 - 1, num2 - 1); // display range from num1 to num2
                    line_num = num2 + 1; // current line will be changed to the next line.
                } else { // only num1
                    editor.printLine(num1 - 1); // display this line
                    line_num = num1 + 1; // current line will be changed to the line following that line
                }
            } else { // no num1
                editor.printLines(); // entire contents of the linked list is displayed
            }
        } else if (command[0] == 'I') {
            std::cout << "Insert command triggered." << std::endl; // Debugging line
            std::stringstream ss(command);
            char I;
            int num;
            ss >> I;

            if (ss >> num) { // get num
                std::string lines_to_insert;
                std::cout << "Enter lines (Ctrl+D to end):" << std::endl;

                while (std::getline(std::cin, lines_to_insert)) {
                    if (lines_to_insert.empty()) {
                        break;
                    }
                    editor.insertLine(num - 1, lines_to_insert); // Insert at specified line
                    line_num++;
                }
            }
        } else if (!command.empty()) {
            std::cout << "Adding new line: " << command << std::endl; // Debugging line
            editor.addLine(command);
            line_num++;
        }
    }

    return 0;
}