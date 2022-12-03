#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

char findDuplicateChar(std::string string1, std::string string2);
uint32_t scoreCharacter(char *c);

int main() {
    // Create a variable to hold the sum of priorities
    uint32_t totalPriorities = 0;

    // Create a file stream to stream data from the input file
    std::fstream inputStream;

    // Create a string variable to hold our input line
    std::string inputLine;

    // Open the file containing our input
    inputStream.open("input.txt");

    // Create some strings to hold each half of the input string
    std::string halve1, halve2;

    // Loop through the lines of the file
    while (std::getline(inputStream, inputLine)) {
        // Read a line from the file
    
        // Split the string into two strings to compare
        uint32_t stringLength = inputLine.length();

        halve1 = inputLine.substr(0, stringLength / 2);
        halve2 = inputLine.substr(stringLength / 2);

        // Find the duplicate character

        char duplicateChar = findDuplicateChar(halve1, halve2);

        // Evaluate the character and add the score to the total
        totalPriorities += scoreCharacter(&duplicateChar);

    }

    // Close the file handle
    inputStream.close();

    std::cout << "Total priorities: " << totalPriorities << std::endl;

    return 0;
}

// Scores a character based on the challenge
uint32_t scoreCharacter(char *c) {
    if (*c > 96 && *c < 123) {
        // Lower case letters
        return (*c - 96);
    } else if (*c > 64 && *c < 91) {
        // Upper case letters
        return (*c - 38);
    }

    // Return 0 if we don't match any letter in a-zA-Z
    return 0;
}

char findDuplicateChar(std::string string1, std::string string2) {
    // Sort the characters in each string using the sort method in the algorithm header
    std::sort(string1.begin(), string1.end());
    std::sort(string2.begin(), string2.end());

    // Variables to hold the first characters of each string
    char c1, c2;

    // Remove the characters from the front of the string after comparison
    while (string1.length() > 0 && string2.length() > 0) {

        // Set the variables to the first characters of each string

        c1 = string1.at(0);
        c2 = string2.at(0);

        // If the characters match, then return the character
        if (c1 == c2) {
            return c1;
        }

        // Compare the characters at the start of each string, remove the one which is smaller in the alphabet
        if (c1 > c2) {
            string2.erase(0,1);
        } else {
            string1.erase(0,1);
        }
    }

    // If we do not find a charcter then return the null character
    return '\0';
}