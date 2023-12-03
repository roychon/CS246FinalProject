#include "ability.h"
using namespace std;

Ability::Ability(Type type) : type{type}, isUsed{false} {}

bool Ability::getIsUsed() { return isUsed; }

Type Ability::getAbilityType() { return type; }

/*
bool Ability::playerMatch(Player *p1, Player *p2) {
    return p1 == p2;
}
*/

void Ability::setTarget(Link *target) {
    targetLink = target;
}
void Ability::setTargetCoords(int x, int y) {
    targetX = x;
    targetY = y;
}
