#include "scan.h"

Scan::Scan(vector<vector<Cell>> *grid): Ability(), grid{grid} {}

void Scan::apply(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (checkValid(x, y)) {
        link->revealLink();
        isUsed = true;
    } else {
        throw(logic_error("Cannot use Scan on that.\n"));
    }
}

bool Scan::checkValid(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (link->getIsRevealed()) return false;
    return true;
}

char Scan::getType() {
    return 'S';
}
