#include "filereader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

// Create a file reader to read data from input.txt
FileReader fr = FileReader("input.txt");;

// Variable to hold the stacks of cargo
std::vector<char> stacks[9];

void parseInputLines();
void parseMove(std::string line);
void printStacks();
void makeMove(int numberOfItems, int from, int to);
void makeMove9001(int numberOfItems, int from, int to);
bool use9001 = false;

int main(int argc, char **argv) {

    // Pass 9001 in as an argument to use the crane9001 as opposed to crane9000
    if (argc > 1 && strcmp(argv[1],"9001") == 0) use9001 = true;

    // Parse the initial stack configuration
    parseInputLines();

    // Print the stacks for debugging purposes
    printStacks();

    // Once we have the initial configuration parse the moves
    std::string lineIn;
    while (fr.readLine(&lineIn)) {
        parseMove(lineIn);
    }

    // Print the stacks, and read off the top value from each to complete this weeks challenge
    printStacks();

    // Close the file reader
    fr.closeFile();

    return 0;
}

// Parses the cargo stacks given initially
void parseInputLines() {

    // A variable to read the data into from the file
    std::string lineIn;

    while (fr.readLine(&lineIn)) {
        // If the line is the number line then exit out of this function
        if (lineIn == " 1   2   3   4   5   6   7   8   9 ") return;

        char charAtIndex;

        for (int i = 0; i < 9; i++) {
            // Index every 4n + 1 index of the input string to get the relevant character (if it exists)
            charAtIndex = lineIn[(4 * i) + 1];

            // If the character is not a space then insert it into the stack
            if (charAtIndex != ' ') {
                stacks[i].insert(stacks[i].begin(), charAtIndex);
            }
        }

    }

}

void parseMove(std::string line) {

    // If the linei s blank then skip over it
    if (line.empty()) return;

    std::string restOfString = line;
    
    // As there are spaces either side of the numbers,
    // find the indexes of sets of spaces and convert
    // the substring between them to a number.

    int spaceIndex = restOfString.find_first_of(' ');

    restOfString = restOfString.substr(spaceIndex + 1);
    spaceIndex = restOfString.find_first_of(' ');
    
    int numItems = std::stoi(restOfString.substr(0, spaceIndex));

    restOfString = restOfString.substr(spaceIndex + 1);
    spaceIndex = restOfString.find_first_of(' ');

    restOfString = restOfString.substr(spaceIndex + 1);
    spaceIndex = restOfString.find_first_of(' ');

    int fromColumn = std::stoi(restOfString.substr(0, spaceIndex));

    restOfString = restOfString.substr(spaceIndex + 1);
    spaceIndex = restOfString.find_first_of(' ');

    restOfString = restOfString.substr(spaceIndex + 1);
    spaceIndex = restOfString.find_first_of(' ');

    int toColumn = std::stoi(restOfString.substr(0, spaceIndex));

    // If we are using the crane9001 then move the items differently
    if (use9001) {
        makeMove9001(numItems, (fromColumn - 1), (toColumn - 1));
    } else {
        makeMove(numItems, (fromColumn - 1), (toColumn - 1));
    }
    
}

// Prints the stacks by iterating through the items in each stack
void printStacks() {
    for (int i = 0; i < 9; i++) {
        std::cout << "Stack " << i << ": ";
        for (int j = 0; j < stacks[i].size(); j++) {
            std::cout << stacks[i][j];
        }

        std::cout << std::endl;
    }
}

void makeMove(int numberOfItems, int from, int to) {
    for (int i = 0; i < numberOfItems; i++) {
        // Iterate through a set number of items

        // Push the item onto the new stack
        stacks[to].push_back(stacks[from].back());

        // Pop the value of the from stack
        stacks[from].pop_back();
    }
}

void makeMove9001(int numberOfItems, int from, int to) {
    for (int i = 0; i < numberOfItems; i++) {
        // Iterate through a set number of items

        // Push the item onto the new stack at the correct position (not just the end)
        stacks[to].insert(stacks[to].end() - i, stacks[from].back());

        // Pop the value of the from stack
        stacks[from].pop_back();
    }
}