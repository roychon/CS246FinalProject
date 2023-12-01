#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "ability.h"
#include "link.h"
class LinkBoost : public Ability {
    Player *activePlayer;
    vector<vector<Cell>> *grid;
    public:
        void apply(int x, int y) override; // TODO: edit move function so it takes into account moveFactor when calculating whether or not is a valid move
        bool checkValid(int x, int y) override;
};

#endif