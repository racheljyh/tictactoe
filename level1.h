#ifndef LEVEL1_H
#define LEVEL1_H
#include <iostream>
#include "strategy.h"
#include "computer.h"

class Level1 : public Strategy {
public:
    Level1(Board *board) : Strategy(board) {}
    void compAddSym(std::string sym) override;
};

#endif