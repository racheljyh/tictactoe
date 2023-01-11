#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include "strategy.h"
#include <iostream> 

class Computer {
    Strategy *s;

public:
    Computer(Strategy *s) : s{s} {}
    void compAddSym(std::string sym) { return s->compAddSym(sym); }
};

#endif