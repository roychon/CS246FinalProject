#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "ability.h"
using namespace std;

class LinkBoost : public Ability {
    Player *activePlayer;
    vector<vector<Cell>> *grid;
    Link *targetLink;
    public:
        LinkBoost(Type type, Player *activePlayer, vector<vector<Cell>> *grid);
        void apply() override; // TODO: edit move function so it takes into account moveFactor when calculating whether or not is a valid move
        bool checkValid() override;
        char getType() override;
        void setTarget(Link *target);
};

#endif