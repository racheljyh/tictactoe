#include <iostream>
#include "level2.h"
#include "strategy.h"

using namespace std;

void Level2::compAddSym(string sym) {
    if (tryWin(sym)) { return; }
    if (tryPreventWin(sym)) { return; }
    randomMove(sym);
}
