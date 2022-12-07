#ifndef DIRTREE_H
#define DIRTREE_H

#include <vector>
#include <iostream>
#include <string>

class DirTree {

    private:
        // Vector to hold the multi-way tree children
        std::vector<DirTree *> children;

        // Variable to hold the size of the file on disk (if not a directory)
        uint32_t sizeOnDisk;
        
        // Holds the directory (file) name
        std::string dirName;

        // Keeps track of the parent of this directory (or file)
        DirTree *parent;

        // A boolean to check whether this instance of DirTree is a directory or file
        bool isDir;

    public:
        DirTree(uint32_t fileSize, std::string directoryName, DirTree *parent, bool isDir);

        // Adds a child to the list of children
        void AddChild(DirTree *child);

        // Returns a pointer to the directories parent
        DirTree* getParent();

        // Getter method for the sizeOnDisk variable
        uint32_t getSizeOnDisk();

        // Getter method for the dirName variable
        std::string getDirName();

        // Getter method for the isDir variable
        bool isDirectory();

        // Prints the directory to stdout
        void printDir(uint16_t depth);

        // Returns the summation of directories below this directory with a total file size less than below
        uint32_t getTotalBelow(uint32_t below);

        // Returns the smallest size of a directory below and including this directory above a set file size
        uint32_t getSmallestSizeAbove(uint32_t above);
};


#endif