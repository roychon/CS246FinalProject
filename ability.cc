#include "ability.h"
using namespace std;

Ability::Ability() : isUsed{false} {}

bool Ability::getIsUsed() { return isUsed; }

bool Ability::playerMatch(Player *p1, Player *p2) {
    return p1 == p2;
}

