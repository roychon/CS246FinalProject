#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "ability.h"
#include "link.h"
#include "cell.h"
class LinkBoost : public Ability {
    Player *activePlayer;
    vector<vector<Cell>> *grid;
    public:
        LinkBoost(Player *activePlayer, vector<vector<Cell>> *grid);
        void apply(int x, int y) override;
        bool checkValid(int x, int y) override;
        char getType() override;
};

#endif
