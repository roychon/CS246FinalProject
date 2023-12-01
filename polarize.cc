#include "polarize.h"

void Polarize::apply(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (link->getType() == 'D') {
        link->setType('V');
    } else link->setType('D');
}

bool checkValid(int x, int y) {}
