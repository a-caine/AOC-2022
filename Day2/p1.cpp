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
    switch (game.at(2)) {
    case 'X':
        scoreGained++;

        if (game.at(0) == 'A') scoreGained += 3; // Draw
        else if (game.at(0) == 'C') scoreGained += 6; // Win

        break;
    case 'Y':
        scoreGained += 2;

        if (game.at(0) == 'B') scoreGained += 3; // Draw
        else if (game.at(0) == 'A') scoreGained += 6; // Win

        break;
    case 'Z':
        scoreGained += 3;

        if (game.at(0) == 'C') scoreGained += 3; // Draw
        else if (game.at(0)== 'B') scoreGained += 6; // Win

        break;
    default:
        std::cerr << "Not a valid move from player!" << std::endl;
        break;
    }

    return scoreGained;
    

}