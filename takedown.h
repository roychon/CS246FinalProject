#ifndef __TAKEDOWN_H__
#define __TAKEDOWN_H__
#include "ability.h"
#include "cell.h"
#include <vector>
#include "link.h"
class Takedown : public Ability {
    Player* activePlayer;
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Takedown(Player* activePlayer, vector<vector<Cell>> *grid);
    void apply(int x, int y) override; // passes in enemy link
    bool checkValid(int x, int y) override;
    char getType() override;
};

#endif
