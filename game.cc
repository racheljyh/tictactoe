#include "game.h"
#include "board.h"

using namespace std;

string Game::getState(int row, int col) const {
    return theBoard->symAt(row, col);
}

string Game::getWinner() const {
    return winner;
}

bool Game::checkDraw() {
    if (checkWin()) { return false; }
    for (int i = 0; i < theBoard->totalSquares(); i++) {
        if (theBoard->getGrid()[i] == " ") { return false; }
    }
    return true;
}

 bool Game::checkWin() {
    string potentialWinner = theBoard->checkWin();
    if (potentialWinner != " ") {
        winner = potentialWinner;
        return true;
    } else { return false; }
 }

Game::~Game() { delete theBoard; }