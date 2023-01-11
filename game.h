#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "subject.h"
#include <string>
#include "board.h"

class Game : public Subject {
    Board *theBoard;
    std::string winner;

public:
    explicit Game(Board *board, std::string winner = "") : theBoard{board} {}
    Board *&board() { return theBoard; }
    std::string getState(int row, int col) const;
    std::string getWinner() const;
    bool checkDraw();
    bool checkWin();
    ~Game();
};

#endif