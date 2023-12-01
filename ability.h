#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "link.h"

class Link;

class Ability
{
    // int id;
    bool isUsed;
public:
    Ability(int id);
    virtual void apply(int x, int y) = 0;
    virtual void checkValid(int x, int y) = 0;
    bool isUsed();
    bool playerMatch(Player *p1, Player *p2);
};

#endif
