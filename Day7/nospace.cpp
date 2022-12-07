#include "filereader.h"
#include "dirtree.h"
#include <iostream>

FileReader fr = FileReader("input.txt");
// Create a directory to act as the root to the root directory
DirTree *currentDirectory = new DirTree(0, "ERROR", nullptr, true);

int main() {
    std::string line;

    // Parse each of the lines into a string
    while (fr.readLine(&line)) {

        // Check if the line is a command
        if (line.at(0) == '$') {
            // Ignore ls as it is not required
            if (line.substr(2, 2) == "ls") continue;
            else if (line.substr(2,2) == "cd") {
                // If the command is changing directory, check if this is going back up or going down
                if (line.substr(5,2) == "..") {
                    // If we are going back up a directory, simply set the current directory to the parent of the previous directory
                    currentDirectory = currentDirectory->getParent();
                } else {
                    // If we are going down a directory, create a new child directory, add it as a child to the current, then switch to the new directory
                    DirTree *child = new DirTree(0, line.substr(5), currentDirectory, true);
                    currentDirectory->AddChild(child);
                    currentDirectory = child;
                }
            }
        } else {
            if (line.substr(0,3) != "dir") {
                // If we have a file, get its size and add it as a child to the current directory
                int fileSize = std::stoi(line.substr(0, line.find_first_of(' ')));

                DirTree* file = new DirTree(fileSize, line.substr(line.find_first_of(' ') + 1), currentDirectory, false);
                currentDirectory->AddChild(file);
            }
        }
    }

    // Firstly find our way to the root of the tree
    while (currentDirectory->getParent()->getDirName() != "ERROR") {
        currentDirectory = currentDirectory->getParent();
    }

    // Print off the directory structure
    currentDirectory->printDir(0);

    // Now that we are at the root (/) loop through all directories and calculate their total weight
    std::cout << "Total size of / " << currentDirectory->getSizeOnDisk() << std::endl;

    std::cout << "Total below 100,000: " << currentDirectory->getTotalBelow(100000) << std::endl;

    std::cout << "Smallest size of directory to delete: " << currentDirectory->getSmallestSizeAbove(30000000 - (70000000 - currentDirectory->getSizeOnDisk())) << std::endl;

    return EXIT_SUCCESS;
}