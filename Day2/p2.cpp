#include <fstream>
#include <string>
#include <iostream>

uint32_t playGame(std::string);

int main() {

    // Create a variable to hold our total score
    uint32_t totalScore = 0;

    // Create a file stream to stream data from the input file
    std::fstream inputStream;

    // Create a string variable to hold our input line
    std::string inputLine;

    // Open the file containing our input
    inputStream.open("input.txt");

    // Loop through the lines of the file
    while (inputStream) {
        // Read a line from the file
        std::getline(inputStream, inputLine);

        if (inputLine.length() == 3) {

            totalScore += playGame(inputLine);
        }
    }

    std::cout << "Total score " << totalScore << std::endl;


    return 0;
}

uint32_t playGame(std::string game) {

    uint32_t scoreGained = 0;

    // Add the score for picking different shape
    switch (game.at(0)) {
    case 'A': // Rock
        switch (game.at(2)) {
        case 'X': // Lose
            scoreGained = 3; // 3 + 0 = 3
            break;
        case 'Y': // Draw
            scoreGained = 4; // 1 + 3 = 4
            break;
        case 'Z': // Win
            scoreGained = 8; // 2 + 6 = 8
            break;
        }
        break;
    case 'B': // Paper
        switch (game.at(2)) {
        case 'X': // Lose
            scoreGained = 1; // 1 + 0 = 1
            break;
        case 'Y': // Draw
            scoreGained = 5; // 2 + 3 = 5
            break;
        case 'Z': // Win
            scoreGained = 9; // 3 + 6 = 9
            break;
        }
        break;
    case 'C': // Scissors
        switch (game.at(2)) {
        case 'X': // Lose
            scoreGained = 2; // 2 + 0 = 2
            break;
        case 'Y': // Draw
            scoreGained = 6; // 3 + 3 = 6
            break;
        case 'Z': // Win
            scoreGained = 7; // 1 + 6 = 7
            break;
        }
        break;
    default:
        std::cerr << "Not a valid move from player!" << std::endl;
        break;
    }

    return scoreGained;
    

}