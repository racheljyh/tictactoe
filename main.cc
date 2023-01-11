#include <iostream>
#include "game.h"
#include "board.h"
#include "computer.h"
#include "textobserver.h"
#include "level1.h"
#include "level2.h"

int setBoardSize() {
    int x;
    while (true) {
        if (!(std::cin >> x)) {
            if (std::cin.eof()) { break; }
            std::cout << "Enter valid board size (integer > 0 and <= 26)." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        } else if (x <= 0 || x > 26) {
            std::cout << "Enter valid board width (integer > 0 and <= 26)." << std::endl;
            std::cin.clear();
            std::cin.ignore();
        } else {
            break;
        }
    }
    return x;
}

int main() {
    // game variables
    std::string command;
    std::string player1;
    std::string player2;
    double p1points = 0;
    double p2points = 0;
    int dimension;
    std::string compLevelP1;
    std::string compLevelP2;

    // begin game
    std::cout << "Enter \"game\" to start a new game" << std::endl;
    while (std::cin >> command) {
        if (command == "game") {
            // set player types
            std::cout << "Enter Player 1 type: \"human\" or \"computer\"" << std::endl;
            while (std::cin >> player1) {
                if (player1 != "human" && player1 != "computer") {
                    std::cout << "Invalid Player Type. Please enter \"human\" or \"computer\"." << std::endl;
                } else if (player1 == "computer") {
                    std::cout << "Enter computer level: \"1\" (easier) or \"2\" (harder)" << std::endl;
                    while (std::cin >> compLevelP1) {
                        if (compLevelP1 != "1" && compLevelP1 != "2") {
                            std::cout << "Invalid Computer Level. Please enter \"1\" (easier) or \"2\" (harder)." << std::endl;
                        } else { break; }
                    }
                    break;
                } else { break; }
            }
            std::cout << "Enter Player 2 type: \"human\" or \"computer\"" << std::endl;
            while (std::cin >> player2) {
                if (player2 != "human" && player2 != "computer") {
                    std::cout << "Invalid Player Type. Please enter \"human\" or \"computer\"." << std::endl;
                } else if (player2 == "computer") {
                    std::cout << "Enter computer level: \"1\" (easier) or \"2\" (harder)" << std::endl;
                    while (std::cin >> compLevelP2) {
                        if (compLevelP2 != "1" && compLevelP2 != "2") {
                            std::cout << "Invalid Computer Level. Please enter \"1\" (easier) or \"2\" (harder)." << std::endl;
                        } else { break; }
                    }
                    break;
                } else { break; }
            }
            // set board size
            std::cout << "Enter board width/height (integer > 0 and <= 26):" << std::endl;
            dimension = setBoardSize();
            Board *board = new Board{dimension};
            Game game{board};
            TextObserver *to = new TextObserver{&game};

            if (player1 == "human" && player2 == "human") {
                std::cout << "Beginning Human vs Human Game" << std::endl;
                int movecount = 0; // if movecount is even -- player1's turn (X); if movecount is odd -- player2's turn (O)
                std::string sym;   // current player's symbol (X or O)
                game.notifyObservers();
                while (std::cin >> command) {
                    if (movecount % 2 == 0) { sym = "X"; }
                    else { sym = "O"; }
                    if (command == "place") {
                        std::cin >> command;
                        try {
                            board->addSym(command, sym);
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        movecount++;
                        if (game.checkWin()) {
                            if (game.getWinner() == "Player 1") { p1points++; }
                            else { p2points++; }
                            std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        if (game.checkDraw()) {
                                p1points += 0.5;
                                p2points += 0.5;
                                std::cout << "Draw!" << std::endl;
                                std::cout << "Enter \"game\" to start a new game" << std::endl;
                                break;
                        }
                    } else if (command == "quit") {
                        std::cout << "Game Ended" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    } else if (command == "undo") {
                        try {
                            board->undo(false);
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        movecount--;
                        continue;
                    } else {
                        std::cout << "Invalid Command." << std::endl;
                        continue;
                    }
                }
                delete to;
            } else if (player1 == "human" && player2 == "computer") {
                std::cout << "Beginning Human vs Computer Game" << std::endl;
                Computer *p2;
                if (compLevelP2 == "1") {
                    Level1 *level1 = new Level1{board};
                    p2 = new Computer{level1};
                } else { 
                    Level2 *level2 = new Level2{board}; 
                    p2 = new Computer{level2};
                }
                game.notifyObservers();
                while (std::cin >> command) {
                    if (command == "place") {
                        std::cin >> command;
                        try {
                            board->addSym(command, "X");
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        if (game.checkWin()) {
                            if (game.getWinner() == "Player 1") { p1points++; }
                            else { p2points++; }
                            std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        if (game.checkDraw()) {
                            p1points += 0.5;
                            p2points += 0.5;
                            std::cout << "Draw!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        p2->compAddSym("O");
                        game.notifyObservers();
                        if (game.checkWin()) {
                            if (game.getWinner() == "Player 1") { p1points++; }
                            else { p2points++; }
                            std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        if (game.checkDraw()) {
                            p1points += 0.5;
                            p2points += 0.5;
                            std::cout << "Draw!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                    } else if (command == "quit") {
                        std::cout << "Game Ended" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    } else if (command == "undo") {
                        try {
                            board->undo(true);
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        continue;
                    } else {
                        std::cout << "Invalid Command." << std::endl;
                        continue;
                    }
                }
                delete to;
            } else if (player1 == "computer" && player2 == "human") {
                std::cout << "Beginning Computer vs Human Game" << std::endl;
                game.notifyObservers();
                Computer *p1;
                if (compLevelP1 == "1") {
                    Level1 *level1 = new Level1{board};
                    p1 = new Computer{level1};
                } else {
                    Level2 *level2 = new Level2{board};
                    p1 = new Computer{level2};
                }
                p1->compAddSym("X");
                game.notifyObservers();
                while (std::cin >> command) {
                    if (command == "place") {
                        std::cin >> command;
                        try {
                            board->addSym(command, "O");
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        if (game.checkWin()) {
                            if (game.getWinner() == "Player 1") { p1points++; }
                            else { p2points++; }
                            std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                            break;
                        }
                        if (game.checkDraw()) {
                            p1points += 0.5;
                            p2points += 0.5;
                            std::cout << "Draw!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        p1->compAddSym("X");
                        game.notifyObservers();
                        if (game.checkWin()) {
                            if (game.getWinner() == "Player 1") { p1points++; }
                            else { p2points++; }
                            std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                            std::cout << "Enter \"game\" to start a new game" << std::endl;
                            break;
                        }
                        if (game.checkDraw()) {
                            p1points += 0.5;
                            p2points += 0.5;
                            std::cout << "Draw!" << std::endl;
                            break;
                        }
                    } else if (command == "quit") {
                        std::cout << "Game Ended" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    } else if (command == "undo") {
                        try {
                            board->undo(true);
                        } catch (const char *error) {
                            std::cout << error << std::endl;
                            continue;
                        }
                        game.notifyObservers();
                        continue;
                    } else { std::cout << "Invalid Command." << std::endl; }
                }
                delete to;
            } else if (player1 == "computer" && player2 == "computer") {
                std::cout << "Beginning Computer vs Computer Game" << std::endl;
                game.notifyObservers();
                Computer *p1;
                Computer *p2;
                if (compLevelP1 == "1") {
                    Level1 *level1 = new Level1{board};
                    p1 = new Computer{level1};
                } else {
                    Level2 *level2 = new Level2{board};
                    p1 = new Computer{level2};
                }
                if (compLevelP2 == "1") {
                    Level1 *level1 = new Level1{board};
                    p2 = new Computer{level1};
                } else {
                    Level2 *level2 = new Level2{board};
                    p2 = new Computer{level2};
                }

                while (true) {
                    p1->compAddSym("X");
                    game.notifyObservers();
                    if (game.checkWin()) {
                        if (game.getWinner() == "Player 1") { p1points++; }
                        else { p2points++; }
                        std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                        break;
                    }
                    if (game.checkDraw()) {
                        p1points += 0.5;
                        p2points += 0.5;
                        std::cout << "Draw!" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    }
                    p2->compAddSym("O");
                    game.notifyObservers();
                    if (game.checkWin()) {
                        if (game.getWinner() == "Player 1") { p1points++; }
                        else { p2points++; }
                        std::cout << "Game Finished! " << game.getWinner() << " wins!" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    }
                    if (game.checkDraw()) {
                        p1points += 0.5;
                        p2points += 0.5;
                        std::cout << "Draw!" << std::endl;
                        std::cout << "Enter \"game\" to start a new game" << std::endl;
                        break;
                    }
                }
                delete to;
            }
        } else { std::cout << "Invalid Command." << std::endl; }
    }
    std::cout << "Final Score:" << std::endl;
    std::cout << "Player 1: " << p1points << std::endl;
    std::cout << "Player 2: " << p2points << std::endl;
    std::cout << "Thanks for playing!" << std::endl;
}