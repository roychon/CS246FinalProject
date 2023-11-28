#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "ability.h"
#include "cell.h"
#include <vector>
#include "link.h"
class Download : public Ability {
    Player *player;
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Download(Player *player, vector<vector<Cell>> *grid, int id);
    void apply(Link &link) override; // passes in enemy link
};

#endif