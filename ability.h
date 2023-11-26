#ifndef __ABILITY_H__
#define __ABILITY_H__
class Ability {
    int abilityType;
    bool isUsed;
public:
    virtual void useAbility() = 0;
};

#endif
