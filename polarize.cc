#include "polarize.h"

Polarize::Polarize(vector<vector<Cell>> *grid): Ability(Type::Polarize), grid{grid} {}

void Polarize::apply(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (link->getType() == 'D') {
        link->setType('V');
    } else link->setType('D');
    isUsed = true;
}

bool Polarize::checkValid(int x, int y) { return false; }

char Polarize::getType() {
    return 'P';
}
