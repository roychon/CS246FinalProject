#include "conceal.h"

Conceal::Conceal(Player *activePlayer, vector<vector<Cell>> *grid) : Ability(), activePlayer{activePlayer} , grid{grid} {}

void Conceal::apply(int x, int y) {
    vector<Link*> links = activePlayer->getLinks();
    for (auto &link :links) {
        if(!link->getIsDead()) {
            link->setRevealedFalse();
            (*grid)[link->getY()][link->getX()].notifyObservers();
        }
    }
    isUsed = true;
}

bool Conceal::checkValid(int x, int y) { return false; }

char Conceal::getType() {
    return 'C';
}
