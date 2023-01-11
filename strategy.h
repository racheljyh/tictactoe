#ifndef STRATEGY_H
#define STRATEGY_H
#include <iostream>
#include <string>
#include "board.h"

class Strategy {
    Board *board;
public:
    Strategy(Board *board) : board{board} {}
    virtual void compAddSym(std::string sym) = 0;
    void randomMove(std::string sym);
    bool tryWin(std::string sym);
    bool tryPreventWin(std::string sym);
};

#endif