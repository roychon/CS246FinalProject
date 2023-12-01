#include "scan.h"

Scan::Scan(vector<vector<Cell>> *grid): Ability{}, grid{grid} {}

void Scan::apply(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (checkValid(x, y)) {
        link->revealLink();
        isUsed = true;
    } else {
        cout << "ability failed" << endl;
    }
}

bool Scan::checkValid(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (link->getIsRevealed()) return false;
    return true;
}

char Scan::getType() {
    return 'S';
}