#include "board.h"
#include <iostream>
#include <string>
using namespace std;

Board::Board(int boardSize) : boardSize{boardSize} {
    for (int i = 0; i < boardSize * boardSize; ++i) {
        boardGrid.emplace_back(" ");
    }
}

Board::~Board() {}

string Board::symAt(int row, int col) {
    if (row < 0 || row > boardSize - 1 || col < 0 || col > boardSize - 1) {
        return " ";
    }
    int index = row * boardSize + col;
    return boardGrid[index];
}

void Board::addSym(string pos, string sym) {
    if (pos.length() != 2) { throw "Invalid Position"; }
    char prow = pos[0];
    char pcol = pos[1];
    if (!isdigit(prow)) { throw "Invalid Position"; }
    if (!islower(pcol)) { throw "Invalid Position"; }
    int row = prow - '0' - 1;
    int col = pcol - 'a';
    if (row >= boardSize || col >= boardSize || row < 0 || col < 0) {
        throw "Invalid Position (out of bounds)";
    }
    int index = row * boardSize + col;
    if (boardGrid[index] != " ") {
        throw "Invalid Position";
    } 
    if (sym == "O" || sym == "X") {
        boardGrid[index] = sym;
        lastMove = index;
        canUndo = true;
    } else {
        throw "Invalid Symbol";
    }
}

void Board::changeSym(int index, std::string sym) { 
    boardGrid[index] = sym;
    compLastMove = index;
}

void Board::undo(bool comp) {
    if (!canUndo) {
        throw "Cannot undo last move.";
    }
    boardGrid[lastMove] = " ";
    canUndo = false;
    if (comp) {
        undoComp();
    }
    cout << "Last move undone. No more undo's available for this turn." << endl;
}

string Board::checkWin() {
    // vertical X win
    for (int i = 0; i < boardSize; ++i) {
        int counter = 0;
        for (int j = 0; j < boardSize; ++j) {
            int index = j * boardSize + i;
            if (boardGrid[index] == "X") { counter++; }
        }
        if (counter == boardSize) {
            return "Player 1";
        }
    }
    // vertical O win
    for (int i = 0; i < boardSize; ++i) {
        int counter = 0;
        for (int j = 0; j < boardSize; ++j) {
            int index = j * boardSize + i;
            if (boardGrid[index] == "O") { counter++; }
        }
        if (counter == boardSize) {
            return "Player 2";
        }
    }

    // horizontal X win
    for (int i = 0; i < boardSize; ++i) {
        int counter = 0;
        for (int j = 0; j < boardSize; ++j) {
            int index = i * boardSize + j;
            if (boardGrid[index] == "X") { counter++; }
        }
        if (counter == boardSize) {
            return "Player 1";
        }
    }
    // horizontal O win
    for (int i = 0; i < boardSize; ++i) {
        int counter = 0;
        for (int j = 0; j < boardSize; ++j) {
            int index = i * boardSize + j;
            if (boardGrid[index] == "O") { counter++; }
        }
        if (counter == boardSize) {
            return "Player 2";
        }
    }

    // asc diagonal X win
    int counter = 0;
    int col = boardSize - 1;
    for (int i = 0; i < boardSize; ++i) {
        int index = i * boardSize + col;
        if (boardGrid[index] == "X") { counter++; }
        col--; 
    }
    if (counter == boardSize) {
        return "Player 1";
    }
    // asc diagonal O win
    counter = 0;
    col = boardSize - 1;
    for (int i = 0; i < boardSize; ++i) {
        int index = i * boardSize + col;
        if (boardGrid[index] == "O") { counter++; }
        col--; 
    }
    if (counter == boardSize) {
        return "Player 2";
    }

    //  dsc diagonal X win
    counter = 0;
    for (int i = 0; i < boardSize; ++i) {
        int index = i * boardSize + i;
        if (boardGrid[index] == "X") { counter++; }
    }
    if (counter == boardSize) {
        return "Player 1";
    }
    // dsc diagonal O win
    counter = 0;
    for (int i = 0; i < boardSize; ++i) {
        int index = i * boardSize + i;
        if (boardGrid[index] == "O") { counter++; }
    }
    if (counter == boardSize) {
        return "Player 2";
    }
    return " ";
}
