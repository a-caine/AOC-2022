#include "filereader.h"
#include <iostream>
#include <vector>
#include <sstream>

FileReader fr("input.txt");

int main() {

    // Create a string to read lines into from the input file
    std::string lineIn;

    uint16_t cycle = 0;
    uint32_t registerX = 1;
    uint8_t cyclesPassed = 0;
    uint32_t totalSignalStrengths = 0;

    std::vector<std::string> instructionsQueue;
    std::vector<std::string> crtOutput;

    std::stringstream crtLine;

    // Read through all of the lines
    while (fr.readLine(&lineIn)) {
        // Push the instruction onto the instruction queue
        instructionsQueue.push_back(lineIn);
    }

    // While there are still instructions in the queue to process, process them
    while (instructionsQueue.size() > 0) {
        // Increase the cycle that we are on
        cycle++;

        // Add to the total signal strength if we need to
        if ((cycle - 20) % 40 == 0) {
            totalSignalStrengths += registerX * cycle;
        }

        // Handle the crt
        uint8_t crtPixel = (cycle % 40) - 1;
        if (crtPixel == (registerX - 1) || crtPixel == registerX || crtPixel == (registerX + 1)) {
            crtLine << "#";
        } else {
            crtLine << ".";
        }

        // Push the crt line onto our output "screen"
        if (cycle % 40 == 0) {
            // If we are on the last cycle of the crt then push the line and clear it
            crtOutput.push_back(crtLine.str());
            crtLine.str("");
        }

        // Then handle the instruction at the head of the queue
        std::string headInstruction = instructionsQueue.at(0).substr(0, 4);

        if (headInstruction == "noop") {
            // If the head instruction is noop then just pop it off the stack and continue
            instructionsQueue.erase(instructionsQueue.begin());
            continue;
        }

        // Otherwise we have an addx function which takes 2 clock cycles to complete

        // If we are on the first cycle, then increase the sub-counter to keep track and move onto the next clock cycle
        if (cyclesPassed < 1) {
            cyclesPassed++;
            continue;
        }

        // If at least one cycle has passed, then we can now execute this instruction
        registerX += std::stoi(instructionsQueue.at(0).substr(5));
        instructionsQueue.erase(instructionsQueue.begin());
        cyclesPassed = 0;
    }

    std::cout << "Total signal strength: " << totalSignalStrengths << std::endl;

    // Print out the crt result
    for (int _ = 0; _ < crtOutput.size(); _++) {
        std::cout << crtOutput.at(_) << std::endl;
    }

    return EXIT_SUCCESS;
}