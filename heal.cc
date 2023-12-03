#include "heal.h"

Heal::Heal(Player *activePlayer) : Ability(), activePlayer{activePlayer} {}

void Heal::apply(int x, int y) {
    if (checkValid(x, y)) {
        activePlayer->decreaseVirusCount();
        isUsed = true;
    } else {
        cout << "ability failed" << endl;
    }
}

bool Heal::checkValid(int x, int y) {
    if (activePlayer->getVirusCount() == 0) {
    return false;
    }
    return true;
}

char Heal::getType() {
    return 'H';
}
