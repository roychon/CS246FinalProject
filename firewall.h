#ifndef __FIREWALL_H__
#define __FIREWALL_H__

#include "ability.h"
using namespace std;

class Firewall : public Ability {
    vector<vector<Cell>> *grid; // pass in grid of the board
    Player *firewallOwner;
public:
    Firewall(Type type, Player *firewallOwner, vector<vector<Cell>> *grid);
    void apply() override;
    bool checkValid() override;
    char getType() override;
};

#endif
