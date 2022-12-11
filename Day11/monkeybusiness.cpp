#include "filereader.h"
#include "monkey.h"

#include <iostream>
#include <vector>

std::vector<Monkey *> monkeys;
std::vector<Monkey *> monkeysPart2;
std::vector<std::pair<int, int> *> monkeyFriends;

void parseItems(std::string items, std::vector<int> *numberVector);
void parseOperation(std::string operation, int *arg1, int *arg2, bool *isAdd);
uint64_t calculateMonkeyBusiness(std::vector<Monkey *> *monkeys);

int main() {
    // First parse all of the monkeys, and fill them with nullptrs
    // but make sure to store their 'friends' that they throw the items to

    FileReader fr("input.txt");

    std::string lineIn;
    int monkeyIndex = -1;

    uint64_t modulus = 1;

    std::vector<int> itemsToAdd;
    int arg1, arg2;
    bool isAddMonkey;
    int testWithDiv;
    int trueMonkeyNum, falseMonkeyNum;

    while (fr.readLine(&lineIn)) {

        if (lineIn.empty()) continue;
        // First strip off the preceding whitespace from the line

        lineIn = lineIn.substr(lineIn.find_first_not_of(' '));

        std::string startOfLine = lineIn.substr(0,2);
        if (startOfLine == "Mo") {
            monkeyIndex++;
        } else if (startOfLine == "St") {
            parseItems(lineIn.substr(15), &itemsToAdd);
        } else if (startOfLine == "Op") {
            parseOperation(lineIn.substr(17), &arg1, &arg2, &isAddMonkey);
        } else if (startOfLine == "Te") {
            testWithDiv = stoi(lineIn.substr(19));
            modulus *= testWithDiv;
        } else if (startOfLine == "If") {
            // Test if we have a true monkey or a false
            if (lineIn.substr(3, 5) == "true:") {
                trueMonkeyNum = std::stoi(lineIn.substr(24));
            } else {
                falseMonkeyNum = std::stoi(lineIn.substr(25));

                // Then create the monkey and add it to the vector as this is the last bit of information we are given about the monkey
                monkeys.push_back(new Monkey(nullptr, nullptr, arg1, arg2, isAddMonkey, testWithDiv));
                monkeysPart2.push_back(new Monkey(nullptr, nullptr, arg1, arg2, isAddMonkey, testWithDiv));

                // Then add all of the items to the monkey
                for (int i = 0; i < itemsToAdd.size(); i++) {
                    monkeys.at(monkeyIndex)->addItem(itemsToAdd.at(i));
                    monkeysPart2.at(monkeyIndex)->addItem(itemsToAdd.at(i));
                }

                // Then clear the list of items for the next monkey
                itemsToAdd.clear();

                // Also push back the monkeys friends
                monkeyFriends.push_back(new std::pair<int, int>(trueMonkeyNum, falseMonkeyNum));
            }
        } else {
            std::cerr << "Unknown line found" << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Once we have parsed the monkeys, then loop through and add the correct pointers

    for (int _ = 0; _ < monkeys.size(); _++) {
        monkeys.at(_)->setMonkey(true, monkeys.at(monkeyFriends.at(_)->first));
        monkeys.at(_)->setMonkey(false, monkeys.at(monkeyFriends.at(_)->second));
        monkeysPart2.at(_)->setMonkey(true, monkeysPart2.at(monkeyFriends.at(_)->first));
        monkeysPart2.at(_)->setMonkey(false, monkeysPart2.at(monkeyFriends.at(_)->second));
    }

    // Now that we have the monkeys, play out each of the rounds

    for (int round = 0; round < 20; round++) {
        // Play out the first round of monkeys
        for (int _ = 0; _ < monkeys.size(); _++) {
            //std::cout << "Monkey " << _ << " taking turn." << std::endl;
            monkeys.at(_)->takeTurn(modulus, true);
        }
    }

    for (int round = 0; round < 10000; round++) {
        for (int _ = 0; _ < monkeysPart2.size(); _++) {
            //std::cout << "Monkey " << _ << " taking turn." << std::endl;
            monkeysPart2.at(_)->takeTurn(modulus, false);
        }       
    }

    // Then print off the number of inspected items by each monkey
    std::cout << "Part 1:" << std::endl;
    for (int _ = 0; _ < monkeys.size(); _++) {
        std::cout << "Monkey " << _ << " inspected items " << monkeys.at(_)->getItemsInspected() << " times." << std::endl;
    }
    std::cout << "Monkey Business: " << unsigned(calculateMonkeyBusiness(&monkeys)) << std::endl;
    
    std::cout << "Part 2:" << std::endl;
    for (int _ = 0; _ < monkeysPart2.size(); _++) {
        std::cout << "Monkey " << _ << " inspected items " << monkeysPart2.at(_)->getItemsInspected() << " times." << std::endl;
    }
    std::cout << "Monkey Business: " << calculateMonkeyBusiness(&monkeysPart2) << std::endl;

    return EXIT_SUCCESS;
}

uint64_t calculateMonkeyBusiness(std::vector<Monkey *> *monkeys) {
    uint64_t largestScore = 0;
    uint64_t secondLargestScore = 0;

    for (int _ = 0; _ < monkeys->size(); _++) {
        uint64_t monkeyScore = monkeys->at(_)->getItemsInspected();
        if (monkeyScore > largestScore) {
            secondLargestScore = largestScore;
            largestScore = monkeyScore;
        } else if (monkeyScore > secondLargestScore) {
            secondLargestScore = monkeyScore;
        }
    }

    return largestScore * secondLargestScore;
}

void parseItems(std::string items, std::vector<int> *numberVector) {

    while (true) {
        // Parse the next item

        // Find the next comma, and split the string up to that position
        std::size_t nextComma = items.find_first_of(',');

        // If there are no more commas then break out of the infinite loop and push the last number into the vector
        if (nextComma == std::string::npos) {
            numberVector->push_back(std::stoi(items));
            break;
        }

        numberVector->push_back(std::stoi(items.substr(0, nextComma)));

        items = items.substr(nextComma + 1);
    }
}

void parseOperation(std::string operation, int *arg1, int *arg2, bool *isAdd) {
    // Parse the first operand

    std::string operand = operation.substr(0, operation.find_first_of(' '));

    if (operand == "old") {
        *arg1 = -1;
    } else {
        *arg1 = std::stoi(operand);
    }

    operation = operation.substr(operation.find_first_of(' ') + 1);

    // Parse the operation

    *isAdd = (operation.at(0) == '+');

    operation = operation.substr(2);

    // Parse second operand
    if (operation == "old") {
        *arg2 = -1;
    } else {
        *arg2 = std::stoi(operation);
    }
}