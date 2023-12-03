#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "ability.h"
#include <vector>

using namespace std;

class Download : public Ability {
    Player *activePlayer; // player that owns the ability
    vector<vector<Cell>> *grid; // pass in grid of the board
public:
    Download(Type type, Player *activePlayer, vector<vector<Cell>> *grid);
    void apply() override; // passes in enemy link
    bool checkValid() override;
    char getType() override;
};

#endif
