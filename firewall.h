#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include "ability.h"
#include "cell.h"
class Firewall : public Ability {
    vector<vector<Cell>> *grid; // pass in grid of the board
    Player *firewallOwner;
public:
    Firewall(Player *firewallOwner, vector<vector<Cell>> *grid);
    void apply(int x, int y) override;
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
