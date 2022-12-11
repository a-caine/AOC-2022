#include "monkey.h"

#include <iostream>

uint64_t Monkey::inspectItem(uint64_t item, uint64_t modulus, bool divThree) {
    // For a set item, get the worry level and test it against the div operand

    // If the monkey is of type add then calculate the add
    if (isAddMonkey) {

        // Then add the operands together
        uint64_t resultOfOperation = ((this->opArg1 == -1) ? item : this->opArg1) + ((this->opArg2 == -1) ? item : this->opArg2);

        // If on part one then divide by three
        if (divThree) resultOfOperation /= 3;

        // Then ensure the result doesn't get too high
        resultOfOperation %= modulus;

        // Then test the result against the divBy
        return resultOfOperation;

    } else {
        // Then multiply the operands together
        uint64_t resultOfOperation = ((this->opArg1 == -1) ? item : this->opArg1) * ((this->opArg2 == -1) ? item : this->opArg2);

        // If on part one then divide by three
        if (divThree) resultOfOperation /= 3;

        // Then ensure the result doesn't get too high
        resultOfOperation %= modulus;

        // Then test the result against the divBy
        return resultOfOperation;
    }
}

Monkey::Monkey(Monkey *falseMonkey, Monkey *trueMonkey, int arg1, int arg2, bool isAdd, int divTest) {
    this->falseMonkey = falseMonkey;
    this->trueMonkey = trueMonkey;

    this->divBy = divTest;
    this->opArg1 = arg1;
    this->opArg2 = arg2;
    this->isAddMonkey = isAdd;
}

void Monkey::takeTurn(uint64_t modulus, bool divThree) {
    // For each turn, inspect each item one by one, decide what to do with it, and throw it to the other monkeys

    this->itemsInspected += this->items.size();

    for (int _ = 0; _ < this->items.size(); _++) {
        uint64_t newItem = inspectItem(this->items.at(_), modulus, divThree);

        if ((newItem % this->divBy) == 0) {
            // If we throw the item to the 'true' monkey
            trueMonkey->addItem(newItem);
        } else {
            falseMonkey->addItem(newItem);
        }      
    }

    // As each monkey will throw all of its items, at the end of the turn, empty its list of items
    this->items.clear();
}

void Monkey::addItem(uint64_t item) {
    this->items.push_back(item);
}

int Monkey::getItemsInspected() {
    return this->itemsInspected;
}

void Monkey::setMonkey(bool monkeyType, Monkey *monkey) {
    if (monkeyType) this->trueMonkey = monkey;
    else this->falseMonkey = monkey;
}

void Monkey::printItems() {
    for (int i = 0; i < this->items.size(); i++) {
        std::cout << unsigned(this->items.at(i)) << ", ";
    }
    
}