#include "dirtree.h"

// Initialises our private variables
DirTree::DirTree(uint32_t fileSize, std::string directoryName, DirTree *parent, bool isDir) {
    this->sizeOnDisk = fileSize;
    this->children = std::vector<DirTree *>();
    this->dirName = directoryName;
    this->parent = parent;
    this->isDir = isDir;
}

// Adds a child to the list of children
void DirTree::AddChild(DirTree *child) {
    this->children.push_back(child);
}

// Returns the size of the file on disk, or size of files in directory on disk
uint32_t DirTree::getSizeOnDisk() {

    uint32_t totalSize = 0;

    // Loop through the children and total their size up
    for (int _ = 0; _ < children.size(); _++) {
        totalSize += children.at(_)->getSizeOnDisk();
    }

    // Add the size of this directory (file) to the total
    totalSize += this->sizeOnDisk;

    return totalSize;
}

// Returns a pointer to the directories parent
DirTree* DirTree::getParent() {
    return this->parent;
}

// Getter method for the dirName variable
std::string DirTree::getDirName() {
    return this->dirName;
}

// Getter method for the isDir variable
bool DirTree::isDirectory() {
    return this->isDir;
}

// Prints the directory to stdout
void DirTree::printDir(uint16_t depth) {
    // Here depth ensures that the directories are aligned in columns to make for easier reading
    if (this->isDir) {
        std::cout << std::string(depth * 2, ' ') << "- " << this->getDirName() << " (dir)" << std::endl;
    } else {
        std::cout << std::string(depth * 2, ' ') << "- " << this->getDirName() << " (file, size=" << this->getSizeOnDisk() << ')' << std::endl;
    }
    
    // Make sure to print children with a different alignment
    for (int _ = 0; _ < children.size(); _++) {
        children.at(_)->printDir(depth + 1);
    }
}

// Returns the summation of directories below this directory with a total file size less than below
uint32_t DirTree::getTotalBelow(uint32_t below) {

    // Only deal with directories so ignore files by returning 0
    if (!isDir) return 0;

    // Total up the child directories to this one
    uint32_t totalBelow = 0;
    for (int _ = 0; _ < children.size(); _++) {
        totalBelow += children.at(_)->getTotalBelow(below);
    }

    // Add the current directory to the total
    if (this->getSizeOnDisk() <= below) totalBelow += this->getSizeOnDisk();

    return totalBelow;
}

// Returns the smallest size of a directory below and including this directory above a set file size
uint32_t DirTree::getSmallestSizeAbove(uint32_t above) {

    // As with getTotalBelow don't deal with files so return INTEGER32_MAX as it will be larger than almost anything
    if (!isDir) return INT32_MAX;
    uint32_t smallestSize = INT32_MAX;

    // Find the smallest size from the children
    for (int _ = 0; _ < children.size(); _++) {
        uint32_t childSize = children.at(_)->getSmallestSizeAbove(above);
        if (childSize >= above && childSize < smallestSize) {
            smallestSize = childSize;
        }
    }

    // Check the current directory against the smallest so far
    uint32_t currentDirSize = this->getSizeOnDisk();
    if (currentDirSize >= above && currentDirSize < smallestSize) {
        smallestSize = currentDirSize;
    }

    // Return the smallest size above the above variable
    return smallestSize;

}