#include "conceal.h"

Conceal::Conceal(Player *activePlayer) : Ability(), activePlayer{activePlayer} {}

void Conceal::apply(int x, int y) {
    vector<Link*> links = activePlayer->getLinks();
    for (auto &link :links) {
        if(!link->getIsDead()) link->setRevealedFalse();
    }
    isUsed = true;
}

bool Conceal::checkValid(int x, int y) { return false; }

char Conceal::getType() {
    return 'C';
}
