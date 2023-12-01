#include "ability.h"
using namespace std;

Ability::Ability(int id) : id{id}, isUsed{false} {}

bool Ability::isUsed() { return isUsed; }

bool playerMatch(Player *p1, Player *p2) {
    return p1 == p2;
}
