#include "dirtree.h"

DirTree::DirTree(uint32_t fileSize, std::string directoryName, DirTree *parent, bool isDir) {
    this->sizeOnDisk = fileSize;
    this->children = std::vector<DirTree *>();
    this->dirName = directoryName;
    this->parent = parent;
    this->isDir = isDir;
}

void DirTree::AddChild(DirTree *child) {
    this->children.push_back(child);
}

uint32_t DirTree::getSizeOnDisk() {
    uint32_t totalSize = 0;
    // Loop through the children and total their size up

    for (int _ = 0; _ < children.size(); _++) {
        totalSize += children.at(_)->getSizeOnDisk();
    }

    totalSize += this->sizeOnDisk;

    return totalSize;
}

DirTree* DirTree::getParent() {
    return this->parent;
}

std::string DirTree::getDirName() {
    return this->dirName;
}

bool DirTree::isDirectory() {
    return this->isDir;
}

void DirTree::printDir(uint16_t depth) {
    if (this->isDir) {
        std::cout << std::string(depth * 2, ' ') << "- " << this->getDirName() << " (dir)" << std::endl;
    } else {
        std::cout << std::string(depth * 2, ' ') << "- " << this->getDirName() << " (file, size=" << this->getSizeOnDisk() << ')' << std::endl;
    }
    
    for (int _ = 0; _ < children.size(); _++) {
        children.at(_)->printDir(depth + 1);
    }
}

uint32_t DirTree::getTotalBelow(uint32_t below) {

    if (!isDir) return 0;

    uint32_t totalBelow = 0;
    for (int _ = 0; _ < children.size(); _++) {
        totalBelow += children.at(_)->getTotalBelow(below);
    }

    if (this->getSizeOnDisk() <= below) totalBelow += this->getSizeOnDisk();

    return totalBelow;
}

uint32_t DirTree::getSmallestSizeAbove(uint32_t above) {

    if (!isDir) return INT32_MAX;
    uint32_t smallestSize = INT32_MAX;

    for (int _ = 0; _ < children.size(); _++) {
        uint32_t childSize = children.at(_)->getSmallestSizeAbove(above);
        if (childSize >= above && childSize < smallestSize) {
            smallestSize = childSize;
        }
    }

    // Check the current directory
    uint32_t currentDirSize = this->getSizeOnDisk();
    if (currentDirSize >= above && currentDirSize < smallestSize) {
        smallestSize = currentDirSize;
    }

    return smallestSize;

}