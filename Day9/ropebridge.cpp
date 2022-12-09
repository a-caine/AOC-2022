#include "filereader.h"
#include <iostream>
#include <vector>

enum direction {
    up = 0,
    right = 1,
    down = 2,
    left = 3
};

std::vector<std::pair<int, int>> previousPositions;

std::vector<std::pair<int, int>> previousPositionsTen;

std::pair<int, int> positions[9];

void printPosition(std::pair<int, int> pos);
bool positionUnique(std::pair<int,int> position);
bool positionUnique10(std::pair<int,int> position);
void moveHeadPosition(std::pair<int,int> *head, std::pair<int,int> *tail, direction dir, int steps);
void moveTail(std::pair<int,int> *head, std::pair<int,int> *tail);
int uniquePositions = 1;
int uniquePositions10 = 1;

FileReader fr("input.txt");

int main() {

    std::pair<int, int> headPos, tailPos;
    
    
    previousPositions.push_back(tailPos);
    previousPositionsTen.push_back(tailPos);

    // Both the headPos and tailPos start at 0,0

    std::string inputLine;

    // Start reading the instructions
    while (fr.readLine(&inputLine)) {
        // Parse the string into the direction and the number

        int numSteps = stoi(inputLine.substr(inputLine.find_first_of(' ')));
        char dir = inputLine.at(0);

        std::cout << "== " << dir << ' ' << numSteps << " ==" << std::endl;

        switch (dir)
        {
        case 'U':
            moveHeadPosition(&headPos, &tailPos, up, numSteps);
            break;
        case 'D':
            moveHeadPosition(&headPos, &tailPos, down, numSteps);
            break;
        case 'L':
            moveHeadPosition(&headPos, &tailPos, left, numSteps);
            break;
        case 'R':
            moveHeadPosition(&headPos, &tailPos, right, numSteps);
            break;
        }
    }

    std::cout << "Number of unique positions: " << uniquePositions << std::endl;
    std::cout << "Number of unique positions with a rope length of 10: " << uniquePositions10 << std::endl;

    return EXIT_SUCCESS;
}

void moveHeadPosition(std::pair<int,int> *head, std::pair<int,int> *tail, direction dir, int steps) {
    // Move the head a set number of steps in a given direction
    int xDiff, yDiff;
    switch (dir)
    {
    case up:
        yDiff = 1;
        xDiff = 0;
        break;
    case down:
        yDiff = -1;
        xDiff = 0;
        break;
    case left:
        xDiff = -1;
        yDiff = 0;
        break;
    case right:
        xDiff = 1;
        yDiff = 0;
        break;
    
    default:
        xDiff = 0;
        yDiff = 0;
        break;
    }

    for (int s = 0; s < steps; s++) {
        // Firstly move the head
        head->first += xDiff;
        head->second += yDiff;

        // Then update the tail
        moveTail(head, tail);

        // Then update the 10 knot tail
        moveTail(head, &positions[0]);

        for (int _ = 1; _ < 9; _++) {
            moveTail(&positions[_ - 1], &positions[_]);
        }

        std::cout << "Moved tail (9) to position: ";
        printPosition(positions[8]);

        // Then check if the tail has moved to a new position
        if (positionUnique(*tail)) {
            // If unique increase the counter
            uniquePositions++;
            // And place the position into the array
            previousPositions.push_back(*tail);
        }

        if (positionUnique10(positions[8])) {
            uniquePositions10++;
            previousPositionsTen.push_back(positions[8]);
        }
    }
}

void moveTail(std::pair<int,int> *head, std::pair<int,int> *tail) {
    // If the tail is still within one tile of the head then do not move it

    int hDist = head->first - tail->first;
    int vDist = head->second - tail->second;

    if (abs(hDist) < 2 && abs(vDist) < 2) return;

    // If we have a distance of more than 2 then figure out where the tail moves
    if (hDist > 1) {
        tail->first = head->first - 1;
        tail->second = head->second;
    } else if (hDist < -1) {
        tail->first = head->first + 1;
        tail->second = head->second;
    } else if (vDist > 1) {
        tail->second = head->second - 1;
        tail->first = head->first;
    } else if (vDist < -1) {
        tail->second = head->second + 1;
        tail->first = head->first;
    }
}

bool positionUnique(std::pair<int,int> position) {

    for (int _ = 0; _ < previousPositions.size(); _++) {
        if (position == previousPositions.at(_)) {
            return false;
        }
    }

    return true;
}

bool positionUnique10(std::pair<int,int> position) {

    for (int _ = 0; _ < previousPositionsTen.size(); _++) {
        if (position == previousPositionsTen.at(_)) return false;
    }

    return true;
}

void printPosition(std::pair<int,int> pos) {
    std::cout << '<' << pos.first << ',' << pos.second << '>' << std::endl;
}