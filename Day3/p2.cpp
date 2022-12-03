#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

std::string findDuplicateCharacters(std::string string1, std::string string2);
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
    std::string lastString;

    uint8_t elf = 0;

    // Loop through the lines of the file
    while (std::getline(inputStream, inputLine)) {
        // Read a line from the file

        // If we are the first elf in the group, then set the last line to our line
        switch (elf) {
        case 0:
            lastString = inputLine;
            elf++;
            break;
        case 1:
            lastString = findDuplicateCharacters(lastString, inputLine);
            elf++;
            break;
        case 2:
            // If we are the last elf in the group then get the repeated character and score it
            lastString = findDuplicateCharacters(lastString, inputLine);
            elf = 0;

            if (lastString.length() < 1) {
                std::cerr << "Length of string is not >1: " << lastString << std::endl;
                break;
            }

            totalPriorities += scoreCharacter(&lastString.at(0));
            break;
        }

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

std::string findDuplicateCharacters(std::string string1, std::string string2) {
    // Sort the characters in each string using the sort method in the algorithm header
    std::sort(string1.begin(), string1.end());
    std::sort(string2.begin(), string2.end());

    // Variables to hold the first characters of each string
    char c1, c2;

    // Variable to hold the output string
    std::string output = "";

    // Remove the characters from the front of the string after comparison
    while (string1.length() > 0 && string2.length() > 0) {

        // Set the variables to the first characters of each string

        c1 = string1.at(0);
        c2 = string2.at(0);

        // If the characters match, then return the character
        if (c1 == c2) {
            output.push_back(c1);

            // Remove the duplicate characters from both strings
            string1.erase(0,1);
            string2.erase(0,1);
        } else if (c1 > c2) { // Compare the characters at the start of each string, remove the one which is smaller in the alphabet
            string2.erase(0,1);
        } else {
            string1.erase(0,1);
        }
    }

    // Return the string containing all duplicate characters
    return output;
}