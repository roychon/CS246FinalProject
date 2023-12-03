#include "scan.h"

Scan::Scan(Type type, vector<vector<Cell>> *grid): Ability(type), grid{grid} {}

void Scan::apply() {
    if (checkValid()) {
        targetLink->revealLink();
        isUsed = true;
    } else {
        cout << "ability failed" << endl;
    }
}

bool Scan::checkValid() {
    if (targetLink->getIsRevealed()) return false;
    return true;
}

char Scan::getType() {
    return 'S';
}
