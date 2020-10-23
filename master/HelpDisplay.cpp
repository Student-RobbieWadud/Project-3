#include <iostream>
#include <iomanip>
#include "HelpDisplay.h"

bool HelpDisplay::print(bool arg_set)
{
        if(!arg_set) return false;

        std::cout << "To use: ./master [options]\n\n";

        std::cout << "Arguments:\n";

        std::cout << "-s x" << "Int value x is the number of slave processes which defaults to 5.\n";

        std::cout << "-l filname" << "The file filename is the file to use which defaults to 'test.out'.\n";

        std::cout << "-t y << Int value y is the time in seconds when the master will terminate itself which defaults to 20.\n";

        return true;
}