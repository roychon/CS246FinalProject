#include "polarize.h"

Polarize::Polarize(Type type, vector<vector<Cell>> *grid): Ability(type), grid{grid} {}

void Polarize::apply() {
    if (targetLink->getType() == 'D') {
        targetLink->setType('V');
    } else if (targetLink->getType() == 'V') {
        targetLink->setType('D');
    } else {
        // need to do error checking for trying to target empty or serverport..
        cout << "failed";
    }
    isUsed = true;
}

bool Polarize::checkValid() { return false; }

char Polarize::getType() {
    return 'P';
}

