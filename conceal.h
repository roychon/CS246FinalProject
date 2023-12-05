#ifndef __CONCEAL_H__
#define __CONCEAL_H__
#include "ability.h"
#include "cell.h"
class Conceal : public Ability {
    Player *activePlayer;
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Conceal(Player *activePlayer, vector<vector<Cell>> *grid);
    void apply(int x, int y) override;
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
