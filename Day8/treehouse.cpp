#include "filereader.h"

#include <iostream>
#include <vector>

enum direction {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};

FileReader fr = FileReader("input.txt");

int ctoi(char c);
void findVisibleTrees(direction dir, int **trees, bool **visibleTrees, int arrSize);
int findViewingDistance(direction dir, int column, int row, int **trees, int arrSize, int treeHeight);

int main() {

    // Read one line to figure out the size of our array to create
    std::string lineIn;

    fr.readLine(&lineIn);

    // Find the length of our string and create an array of that size
    int arrSize = lineIn.length();

    // Array to hold the trees, [row][column]
    //int trees[arrSize][arrSize];
    int **trees;
    trees = new int *[arrSize];
    for (int i = 0; i < arrSize; i++) trees[i] = new int[arrSize];

    // Array to hold whether the trees are visible or not ([row][column])
    //bool isVisible[arrSize][arrSize];
    bool **isVisible;
    isVisible = new bool *[arrSize];
    for (int i = 0; i < arrSize; i++) isVisible[i] = new bool[arrSize];

    // Fill the first row of the array in
    for (int c = 0; c < arrSize; c++) {
        trees[0][c] = ctoi(lineIn.at(c));
    }

    // Fill out the rest of the array
    for (int r = 1; r < arrSize; r++) {
        // Read in a line, if we run out of lines, then fail
        if (!fr.readLine(&lineIn)) {
            std::cerr << "Failed to read row " << r << " not enough lines in file" << std::endl;
            return EXIT_FAILURE;
        } 

        // Then populate the array
        for (int c = 0; c < arrSize; c++) {
            trees[r][c] = ctoi(lineIn.at(c));
        }
    }

    // Then find the number of trees visible
    findVisibleTrees(North, trees, isVisible, arrSize);
    findVisibleTrees(East, trees, isVisible, arrSize);
    findVisibleTrees(South, trees, isVisible, arrSize);
    findVisibleTrees(West, trees, isVisible, arrSize);

    // Total the number of trees

    int totalVisible = 0;

    for (int r = 0; r < arrSize; r++) {
        for (int c = 0; c < arrSize; c++) {
            if (isVisible[r][c]) totalVisible++;
        }
    }

    std::cout << "Total visible trees: " << totalVisible << std::endl;

    // Part 2

    int maxScenicScore = 0;
    int currScenicScore;

    for (int r = 0; r < arrSize; r++) {
        for (int c = 0; c < arrSize; c++) {
            // Find the scenic score for each position in the forest
            currScenicScore = findViewingDistance(North, c, r, trees, arrSize, trees[r][c]) * findViewingDistance(East, c, r, trees, arrSize, trees[r][c]) * findViewingDistance(South, c, r, trees, arrSize, trees[r][c]) * findViewingDistance(West, c, r, trees, arrSize, trees[r][c]);
            // Update the maximum scenic score if the current scenic score is higher
            if (currScenicScore > maxScenicScore) maxScenicScore = currScenicScore;
        }
    }

    std::cout << "Maximum scenic score: " << maxScenicScore << std::endl;

    return EXIT_SUCCESS;
}

void findVisibleTrees(direction dir, int **trees, bool **visibleTrees, int arrSize) {
    // Variables to track the tallest tree and the current height of the tree we are on
    int maxHeight, treeHeight;

    switch (dir)
    {
    case North:
        for (int c = 0; c < arrSize; c++) {
            int maxHeight = -1;

            // Work our way towards the center and set the trees to be visible
            for (int r = 0; r < arrSize; r++) {
                treeHeight = trees[r][c];
                // compare the current tree to the current highest tree, if greater it is visible, if 9 break as no other tree will be visible
                if (treeHeight > maxHeight) {
                    visibleTrees[r][c] = true;
                    if (treeHeight == 9) break;
                    maxHeight = treeHeight;
                }
            }
        }
        break;
    case East:
        for (int r = 0; r < arrSize; r++) {
            int maxHeight = -1;

            // Work our way towards the center and set the trees to be visible
            for (int c = (arrSize - 1); c >= 0; c--) {
                treeHeight = trees[r][c];
                // compare the current tree to the current highest tree, if greater it is visible, if 9 break as no other tree will be visible
                if (treeHeight > maxHeight) {
                    visibleTrees[r][c] = true;
                    if (treeHeight == 9) break;
                    maxHeight = treeHeight;
                }
            }
        }
        break;
    case South:
        for (int c = 0; c < arrSize; c++) {
            int maxHeight = -1;

            // Work our way towards the center and set the trees to be visible
            for (int r = (arrSize - 1); r >= 0; r--) {
                treeHeight = trees[r][c];
                // compare the current tree to the current highest tree, if greater it is visible, if 9 break as no other tree will be visible
                if (treeHeight > maxHeight) {
                    visibleTrees[r][c] = true;
                    if (treeHeight == 9) break;
                    maxHeight = treeHeight;
                }
            }
        }
        break;
    case West:
        for (int r = 0; r < arrSize; r++) {
            int maxHeight = -1;

            // Work our way towards the center and set the trees to be visible
            for (int c = 0; c < arrSize; c++) {
                treeHeight = trees[r][c];
                // compare the current tree to the current highest tree, if greater it is visible, if 9 break as no other tree will be visible
                if (treeHeight > maxHeight) {
                    visibleTrees[r][c] = true;
                    if (treeHeight == 9) break;
                    maxHeight = treeHeight;
                }
            }
        }
        break;
    }
}

int findViewingDistance(direction dir, int column, int row, int **trees, int arrSize, int treeHeight) {
    // Keep track of the height of the tree in the array and the distance away from the initial tree we have gone
    int arrTreeHeight;
    int distance = 0;

    switch (dir)
    {
    case North:
        // Work our way outwards from the tree towards the edge
        for (int r = row - 1; r >= 0; r--) {
            arrTreeHeight = trees[r][column];
            // compare the current tree to the starting tree, if it is smaller then keep going
            if (arrTreeHeight < treeHeight) {
                distance++;
            } else {
                // If it is not smaller then increase the distance, but then break as no more trees are visible
                distance++;
                break;
            }
        }
        break;
    case East:
        // Work our way outwards from the tree towards the edge
        for (int c = column + 1; c < arrSize; c++) {
            arrTreeHeight = trees[row][c];
            // compare the current tree to the starting tree, if it is smaller then keep going
            if (arrTreeHeight < treeHeight) {
                distance++;
            } else {
                // If it is not smaller then increase the distance, but then break as no more trees are visible
                distance++;
                break;
            }
        }
        break;
    case South:
        // Work our way outwards from the tree towards the edge
        for (int r = row + 1; r < arrSize; r++) {
            arrTreeHeight = trees[r][column];
            // compare the current tree to the starting tree, if it is smaller then keep going
            if (arrTreeHeight < treeHeight) {
                distance++;
            } else {
                // If it is not smaller then increase the distance, but then break as no more trees are visible
                distance++;
                break;
            }
        }
        break;
    case West:
        // Work our way outwards from the tree towards the edge
        for (int c = column - 1; c >= 0; c--) {
            arrTreeHeight = trees[row][c];
            // compare the current tree to the starting tree, if it is smaller then keep going
            if (arrTreeHeight < treeHeight) {
                distance++;
            } else {
                // If it is not smaller then increase the distance, but then break as no more trees are visible
                distance++;
                break;
            }
        }
        break;
    }

    // Return the distance travelled
    return distance;
}

// Converts a character into its integer equivalent e.g. ctio('4') returns 4
int ctoi(char c) {
    return (c - '0');
}