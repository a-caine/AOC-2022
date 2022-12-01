#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// Create a variable to handle the max calories
uint32_t mostCalories = 0;
uint32_t secondMostCalories = 0;
uint32_t thirdMostCalories = 0;

void updateMax(uint32_t calories);
void updateMost(uint32_t calories);
void updateSecondMost(uint32_t calories);
void updateThirdMost(uint32_t calories);

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

    // Once we have finished updateMax to add the last elves value
    updateMax(currentCalorieCount);

    // Print the total value to the screen
    std::cout << (mostCalories + secondMostCalories + thirdMostCalories) << std::endl;
}

// Updates the maximum calorie value if the input is larger than the current max
void updateMax(uint32_t calories) {
    if (calories > mostCalories) {
        updateMost(calories);
    } else if (calories > secondMostCalories) {
        updateSecondMost(calories);
    } else if (calories > thirdMostCalories) {
        updateThirdMost(calories);
    }
}

// Update the mostCalories value and cascade the current values downwards
void updateMost(uint32_t calories) {
    updateSecondMost(mostCalories);
    mostCalories = calories;
}

// Update the secondMostCalories value and cascade the current value downwards
void updateSecondMost(uint32_t calories) {
    updateThirdMost(secondMostCalories);
    secondMostCalories = calories;
}

// Update the thirdMostCalories value
void updateThirdMost(uint32_t calories) {
    thirdMostCalories = calories;
}