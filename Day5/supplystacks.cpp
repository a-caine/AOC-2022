#include "filereader.h"
#include <iostream>
#include <vector>
#include <algorithm>

FileReader fr = FileReader("input.txt");;

std::vector<char> stacks[9];

void parseInputLines();
void parseMove(std::string line);
void printStacks();
void makeMove(int numberOfItems, int from, int to);

int main() {

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

    fr.closeFile();

    return 0;
}

void parseInputLines() {

    std::string lineIn;

    while (fr.readLine(&lineIn)) {
        // If the line is the number line then exit out of this function
        if (lineIn == " 1   2   3   4   5   6   7   8   9 ") return;

        // Replace every 4th character in the line with a comma
        for (int i = 1; (i * 4) - 1 < lineIn.length(); i++) {
            lineIn[(i * 4) - 1] = ',';
        }

        // Remove all whitespace and brackets from the line
        lineIn.erase(std::remove(lineIn.begin(), lineIn.end(), ' '), lineIn.end());
        lineIn.erase(std::remove(lineIn.begin(), lineIn.end(), ']'), lineIn.end());
        lineIn.erase(std::remove(lineIn.begin(), lineIn.end(), '['), lineIn.end());

        // Now find the characters between the commas and insert them into the correct stacks
        int stack = 0;
        char charAtIndex;

        for (int i = 0; i < lineIn.length(); i++) {
            charAtIndex = lineIn.at(i);

            if (charAtIndex == ',') {
                stack++;
            } else {
                stacks[stack].insert(stacks[stack].begin(), charAtIndex);
            }       
        }

    }

}

void parseMove(std::string line) {

    // If the linei s blank then skip over it
    if (line.empty()) return;

    std::string restOfString = line;
    // Find the number of items to move

    // Find the first instance of a space

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

    std::cout << "Moving " << numItems << " items from stack " << fromColumn << " to stack " << toColumn << "." << std::endl;

    makeMove(numItems, (fromColumn - 1), (toColumn - 1));
}

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