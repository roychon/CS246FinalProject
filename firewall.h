#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include "ability.h"
#include "cell.h"
class Firewall : public Ability {
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Firewall(vector<vector<Cell>> *grid, int id);
    void apply(Link &link) override; // passes in enemy link
};

#endif