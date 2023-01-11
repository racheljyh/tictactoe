#ifndef LEVEL2_H
#define LEVEL2_H
#include <iostream>
#include "strategy.h"
#include "computer.h"

class Level2 : public Strategy {
public:
    Level2(Board *board) : Strategy(board) {}
    void compAddSym(std::string sym) override;
};

#endif