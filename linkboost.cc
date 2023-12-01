#include "linkboost.h"

void LinkBoost::apply(int x, int y) {
    if (checkValid(x, y)) {
        Link *link = (*grid)[x][y].getLink();
        link->incrementMoveFactor(1);
        isUsed = true;
    } else {
        cout << "INVALID ABILITY MOVE" << endl;
    }
}

bool LinkBoost::checkValid(int x, int y) {
    return playerMatch(activePlayer, &(*grid)[x][y].getPlayer());
}
