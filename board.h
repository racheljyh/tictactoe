#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>

class Board {
private:
    int boardSize;
    std::vector<std::string> boardGrid;
    int lastMove;
    int compLastMove = 0;
    bool canUndo = false;
public:
    Board(int boardSize);
    ~Board();

    // board dimension functions 
    int getDimension() { return boardSize; }
    int totalSquares() { return (boardSize * boardSize); }

    std::string symAt(int row, int col);
    void addSym(std::string pos, std::string sym);
    void changeSym(int index, std::string sym);
    void undoComp() { boardGrid[compLastMove] = " "; }
    void undo(bool comp);
    std::vector<std::string> getGrid() { return boardGrid; }
    std::string checkWin();
};

#endif