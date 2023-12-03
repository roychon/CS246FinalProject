#ifndef __ABILITY_H__
#define __ABILITY_H__
#include "link.h"
#include "player.h"
#include <iostream>
#include "cell.h"

class Link;
class Player;
class Cell;

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
public:
    explicit Ability(Type type);
    virtual void apply(int x, int y) = 0;
    virtual bool checkValid(int x, int y) = 0;
    virtual char getType() = 0;
    bool getIsUsed();
    Type getAbilityType();
    bool playerMatch(Player *p1, Player *p2);
};

#endif
