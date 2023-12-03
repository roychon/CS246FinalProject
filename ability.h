#ifndef __ABILITY_H__
#define __ABILITY_H__
#include <iostream>
#include "link.h"
#include "cell.h"

class Player;

enum class Type {
    Download,
    Firewall,
    Polarize,
    LinkBoost,
    Scan
};

class Ability {
    Type type;
protected:
    bool isUsed;
    Link *targetLink;
    int targetX, targetY;
public:
    explicit Ability(Type type);
    virtual void apply() = 0;
    virtual bool checkValid() = 0;
    virtual char getType() = 0;
    bool getIsUsed();
    Type getAbilityType();
    // bool playerMatch(Player *p1, Player *p2);
    void setTarget(Link *link);
    void setTargetCoords(int x, int y);
};

#endif
