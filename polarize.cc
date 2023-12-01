#include "polarize.h"

Polarize::Polarize(vector<vector<Cell>> *grid): Ability{}, grid{grid} {}

void Polarize::apply(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (link->getType() == 'D') {
        link->setType('V');
    } else link->setType('D');
    isUsed = true;
}

bool Polarize::checkValid(int x, int y) { return false; }
