#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "link.h"

class Link;

class Ability
{
    int id;
    bool isUsed;
public:
    Ability(int id);
    int getId();
    virtual void apply(Link &link) = 0;
    bool isUsed();
};

#endif
