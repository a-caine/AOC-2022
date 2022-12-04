#include "filereader.h"
#include <iostream>

bool isFullyInside(uint32_t min1, uint32_t max1, uint32_t min2, uint32_t max2);
bool isPartiallyInside(uint32_t min1, uint32_t max1, uint32_t min2, uint32_t max2);

int main() {
    // Create a file stream object to read data from the input
    FileReader fReader = FileReader("input.txt");
    
    // Create a variable to hold the next line read in from memory
    std::string lineIn;

    uint16_t totalFullyInside = 0;
    uint16_t totalIntersection = 0;

    // Use our instance of the fReader class to read lines in
    while (fReader.readLine(&lineIn)) {
        // Split the lines on the comma
        uint16_t charPosition = lineIn.find_first_of(',');

        // Split the line on the comma
        std::string elf1, elf2;
        elf1 = lineIn.substr(0, charPosition);
        elf2 = lineIn.substr(++charPosition);

        // Find the minimum and maximum values of the elves locations
        // Create variables to hold this information
        uint32_t elf1Min, elf1Max, elf2Min, elf2Max;
        std::string min, max;

        // Elf 1

        // Re use charPosition
        charPosition = elf1.find_first_of('-');
        min = elf1.substr(0, charPosition);
        max = elf1.substr(++charPosition);

        // Convert the strings into integers
        elf1Min = std::stoi(min);
        elf1Max = std::stoi(max);

        // Elf 2
        // Re use charPosition
        charPosition = elf2.find_first_of('-');
        min = elf2.substr(0, charPosition);
        max = elf2.substr(++charPosition);

        // Convert the strings into integers
        elf2Min = std::stoi(min);
        elf2Max = std::stoi(max);

        if (isFullyInside(elf1Min, elf1Max, elf2Min, elf2Max)) totalFullyInside++;
        if (isPartiallyInside(elf1Min, elf1Max, elf2Min, elf2Max)) totalIntersection++;
    }

    std::cout << "Number fully inside: " << totalFullyInside << std::endl;
    std::cout << "Number partially inside: " << totalIntersection << std::endl;

    return 0;
}

// Decides whether two pairs fully contain one another or not
bool isFullyInside(uint32_t min1, uint32_t max1, uint32_t min2, uint32_t max2) {
    if (min1 >= min2 && max1 <= max2) return true;

    if (min1 <= min2 && max1 >= max2) return true;

    return false;
}

// Decide whether two pairs intersect or not
bool isPartiallyInside(uint32_t min1, uint32_t max1, uint32_t min2, uint32_t max2) {
    if (min1 >= min2 && min1 <= max2) return true;
    
    if (min2 >= min1 && min2 <= max1) return true;

    return false;
}

