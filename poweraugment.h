#ifndef __POWERAUGMENT_H__
#define __POWERAUGMENT_H__
#include "ability.h"
#include "cell.h"
class PowerAugment : public Ability {
    vector<vector<Cell>> *grid; // pass in grid of the board
    Player *activePlayer;
public:
    PowerAugment(Player *activePlayer, vector<vector<Cell>> *grid);
    void apply(int x, int y) override;
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
