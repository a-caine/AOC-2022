#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// Create a variable to handle the max calories
uint32_t maxCalories = 0;

void updateMax(uint32_t calories);

int main() {

    // Create a file stream to stream data from the input file
    std::fstream inputStream;

    // Create a string variable to hold our input line
    std::string inputLine;

    // Create a variable to hold the current calorie count (of the current elf)
    uint32_t currentCalorieCount = 0;

    // Open the file containing our input
    inputStream.open("input.txt");

    // Loop through the lines of the file
    while (inputStream) {
        // Read a line from the file
        std::getline(inputStream, inputLine);

        if (inputLine.empty()) {
            
            // If the line is empty then we have finished with the current elf 
            // and need to check their total against the highest total

            updateMax(currentCalorieCount);

            // Then reset the counter for the next elf
            currentCalorieCount = 0;

        } else {
            // If the line is not blank then add the calories in the line to the current count
            currentCalorieCount += std::stoi(inputLine);
            
        }
    }

    // Once we have finished updateMax to add the last elves values
    updateMax(currentCalorieCount);

    // Print the maximum value to the screen
    std::cout << maxCalories << std::endl;
}

// Updates the maximum calorie value if the input is larger than the current max
void updateMax(uint32_t calories) {
    if (calories > maxCalories) maxCalories = calories;
}