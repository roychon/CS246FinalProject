#include "scan.h"

void Scan::apply(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (checkValid(x, y)) {
        link->revealLink();
        isUsed = true;
    } else {
        cout << "ability failed" << endl;
    }
}

bool checkValid(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (link->getIsRevealed()) return false;
}
