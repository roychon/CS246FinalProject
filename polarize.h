#ifndef __POLARIZE_H__
#define __POLARIZE_H__
#include "ability.h"
#include "link.h"

class Polarize : public Ability {
    vector<vector<Cell>> *grid;
    Player *activePlayer;
    public:
        Polarize(Player* activePlayer, vector<vector<Cell>> *grid);
        void apply(int x, int y) override;
        bool checkValid(int x, int y) override;
        char getType() override;
};

#endif
