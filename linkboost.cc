#include "linkboost.h"

LinkBoost::LinkBoost(Type type, Player *activePlayer, vector<vector<Cell>> *grid) : Ability(type), activePlayer{activePlayer}, grid{grid} {}

void LinkBoost::apply() {
    targetLink->incrementMoveFactor(1);
    isUsed = true;
}

bool LinkBoost::checkValid() {
    // we can probably do this check before
   // return playerMatch(activePlayer, &((*grid)[][x].getLink()->getPlayer()));
   return false;
}

char LinkBoost::getType() {
    return 'L';
}

void LinkBoost::setTarget(Link *target) {
    targetLink = target;
}
