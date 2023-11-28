#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "link.h"
class Ability {
    int id;
    bool isUsed;
public:
    Ability(int abilityType);
    virtual void apply(Link &link) = 0;
};

#endif
