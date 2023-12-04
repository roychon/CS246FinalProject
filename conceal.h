#ifndef __CONCEAL_H__
#define __CONCEAL_H__
#include "ability.h"
#include "cell.h"
class Conceal : public Ability {
    Player *activePlayer;
public:
    // hides all living links' information 
    Conceal(Player *activePlayer);
    void apply(int x, int y) override;
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
