#ifndef DIRTREE_H
#define DIRTREE_H

#include <vector>
#include <iostream>
#include <string>

class DirTree {

    private:
        std::vector<DirTree *> children;
        uint32_t sizeOnDisk;
        std::string dirName;
        DirTree *parent;
        bool isDir;

    public:
        DirTree(uint32_t fileSize, std::string directoryName, DirTree *parent, bool isDir);

        void AddChild(DirTree *child);

        DirTree* getParent();

        uint32_t getSizeOnDisk();

        std::string getDirName();

        bool isDirectory();

        void printDir(uint16_t depth);

        uint32_t getTotalBelow(uint32_t below);

        uint32_t getSmallestSizeAbove(uint32_t above);
};


#endif