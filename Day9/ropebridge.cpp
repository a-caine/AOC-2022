#include "filereader.h"
#include <iostream>
#include <vector>
#include <set>

enum direction {
    up = 0,
    right = 1,
    down = 2,
    left = 3
};

// Sets to hold the previous positions of the first and ninth knots
std::set<std::pair<int, int>> previousPositions;
std::set<std::pair<int, int>> previousPositionsTen;

// Holds the list of knots
std::pair<int, int> positions[9];

void moveHeadPosition(std::pair<int,int> *head, direction dir, int steps);
void moveTail(std::pair<int,int> *head, std::pair<int,int> *tail);
void printPositionBoard(std::pair<int, int> *head);

// File reader to read input
FileReader fr("input.txt");

int main() {

    // Keep track of the head of the rope
    std::pair<int, int> headPos;
    
    // Insert the default position of the first knot into the map
    previousPositions.insert(std::pair<int, int>(0,0));

    // A string to read the lines of input into
    std::string inputLine;

    // Print the initial state of the board
    printPositionBoard(&headPos);

    // Start reading the instructions
    while (fr.readLine(&inputLine)) {
        // Parse the string into the direction and the number
        int numSteps = stoi(inputLine.substr(inputLine.find_first_of(' ')));
        char dir = inputLine.at(0);

        std::cout << "== " << dir << ' ' << numSteps << " ==" << std::endl;

        switch (dir)
        {
        case 'U':
            moveHeadPosition(&headPos, up, numSteps);
            break;
        case 'D':
            moveHeadPosition(&headPos, down, numSteps);
            break;
        case 'L':
            moveHeadPosition(&headPos, left, numSteps);
            break;
        case 'R':
            moveHeadPosition(&headPos, right, numSteps);
            break;
        }

        // Print the board after each step
        printPositionBoard(&headPos);
    }

    std::cout << "Number of unique positions of the first knot (Part 1): " << previousPositions.size() << std::endl;
    std::cout << "Number of unique positions of the ninth knot (Part 2): " << previousPositionsTen.size() << std::endl;

    return EXIT_SUCCESS;
}

void moveHeadPosition(std::pair<int,int> *head, direction dir, int steps) {
    // Move the head a set number of steps in a given direction
    int xDiff = 0;
    int yDiff = 0;
    switch (dir)
    {
    case up:
        yDiff = 1;
        break;
    case down:
        yDiff = -1;
        break;
    case left:
        xDiff = -1;
        break;
    case right:
        xDiff = 1;
        break;
    }

    // Move in this direction the correct number of times
    for (int s = 0; s < steps; s++) {

        // Firstly move the head
        head->first += xDiff;
        head->second += yDiff;

        // Then update the 10 knot tail
        moveTail(head, &positions[0]);

        for (int _ = 1; _ < 9; _++) {
            moveTail(&positions[_ - 1], &positions[_]);
        }
        
        // Add the positions of the first knot and the 9th knot for parts 1 and 2
        previousPositions.insert(positions[0]);
        previousPositionsTen.insert(positions[8]);
    }
}

// Moves the tail by referencing the head
void moveTail(std::pair<int,int> *head, std::pair<int,int> *tail) {
    // Calculate the horizontal and vertical distance from head to tail
    int hDist = head->first - tail->first;
    int vDist = head->second - tail->second;

    // If the tail is still within one tile of the head then do not move it
    if (abs(hDist) < 2 && abs(vDist) < 2) return;
    

    // Otherwise move the tail to follow the head
    if (hDist > 0) tail->first += 1;
    else if (hDist < 0) tail->first -= 1;

    if (vDist > 0) tail->second += 1;
    else if (vDist < 0) tail->second -= 1;
}


void printPositionBoard(std::pair<int, int> *head) {
    //First find the maximum and minimum positions
    int minX, maxX, minY, maxY;

    minX = positions[0].first;
    maxX = positions[0].first;

    minY = positions[0].second;
    maxY = positions[0].second;

    for (int _ = 1; _ < 9; _++) {
        if (positions[_].first < minX) minX = positions[_].first;

        if (positions[_].first > maxX) maxX = positions[_].first;

        if (positions[_].second < minY) minY = positions[_].second;

        if (positions[_].second > maxY) maxY = positions[_].second;
    }

    std::cout << "Printing board with min/max x: " << minX << ',' << maxX << " and min/max y: " << minY << ',' << maxY << std::endl;
    
    // Then loop through the positions and print them onto a grid bounded by the maximum and minumum x and y positions
    for (int y = maxY; y >= minY; y--) {
        for (int x = minX; x <= maxX; x++) {
            int positionsIndex = -1;

            for (int _ = 8; _ >= 0; _--) {
                if (positions[_].first == x && positions[_].second == y) {
                    positionsIndex = _;
                }
            }

            if (head->first == x && head->second == y) {
                std::cout << "H";
            } else if (x == 0 && y == 0) {
                std::cout << "s";
            } else if (positionsIndex == -1) {
                std::cout << ".";
            } else {
                std::cout << (positionsIndex + 1);
            }

        }
        std::cout << std::endl;
    }
    
}