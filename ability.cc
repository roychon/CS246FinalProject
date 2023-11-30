#include "ability.h"
using namespace std;

Ability::Ability(int id) : id{id}, isUsed{false} {}

int Ability::getId() { return id; }

bool Ability::isUsed() { return isUsed; }
