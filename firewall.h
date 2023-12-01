#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include "ability.h"
#include "cell.h"
class Firewall : public Ability {
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Firewall(vector<vector<Cell>> *grid);
    void apply(int x, int y) override; // passes in enemy link
    bool checkValid(int x, int y) override;
};

#endif