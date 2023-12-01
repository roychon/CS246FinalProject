#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "ability.h"
#include "cell.h"
#include <vector>
#include "link.h"
class Download : public Ability {
    Player *activePlayer; // player that owns the ability
    // Player *inactivePlayer;
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Download(Player *activePlayer, Player *inactivePlayer, vector<vector<Cell>> *grid);
    void apply(int x, int y) override; // passes in enemy link
};

#endif
