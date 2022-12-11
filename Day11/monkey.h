#ifndef MONKEY_H
#define MONKEY_H

#include <vector>
#include <iostream>
#include <cstddef>

class Monkey {
    private:
        Monkey *falseMonkey;
        Monkey *trueMonkey;

        int divBy;
        std::vector<uint64_t> items;

        int opArg1, opArg2;
        bool isAddMonkey;

        int itemsInspected = 0;

        uint64_t inspectItem(uint64_t item, uint64_t modulus, bool divThree);

    public:
        Monkey(Monkey *falseMonkey, Monkey *trueMonkey, int arg1, int arg2, bool isAdd, int divTest);

        void takeTurn(uint64_t modulus, bool divThree);

        void addItem(uint64_t item);

        int getItemsInspected();

        void setMonkey(bool monkeyType, Monkey *monkey);

        void printItems();
};


#endif