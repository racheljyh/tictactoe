#include "strategy.h"
#include <random>
#include <iostream>

void Strategy::randomMove(std::string sym) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> randInt(0, board->totalSquares() - 1);
    while (true) {
        int index = randInt(rng);
        if (board->getGrid()[index] != " ") {
            continue;
        } else {
            board->changeSym(index, sym);
            break;
        }
    }
}

bool Strategy::tryPreventWin(std::string sym) {
    std::string opp; 
    if (sym == "X") { opp = "O"; }
    else { opp = "X"; }
    for (int i = 0; i < board->totalSquares(); ++i) {
        if (board->getGrid()[i] == " ") {
            // place opponent's symbol on the board to see if this move would result in a win
            board->changeSym(i, opp);
            if (board->checkWin() != " ") {
                board->changeSym(i, sym);
                return true;
            } else { board->changeSym(i, " "); }
        }
    }
    return false;
}

bool Strategy::tryWin(std::string sym) {
    for (int i = 0; i < board->totalSquares(); ++i) {
        if (board->getGrid()[i] == " ") {
            // place symbol on the board to see if this move would result in a win
            board->changeSym(i, sym);
            if (board->checkWin() != " ") {
                return true;
            } else { board->changeSym(i, " "); }
        }
    }
    return false;
}
