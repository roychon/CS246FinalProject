#ifndef __HEAL_H__
#define __HEAL_H__
#include "ability.h"
#include "cell.h"
class Heal : public Ability {
    Player *activePlayer;
public:
    Heal(Player *activePlayer);
    void apply(int x, int y) override;
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
