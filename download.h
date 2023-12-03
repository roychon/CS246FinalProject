#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__
#include "ability.h"
#include "cell.h"
#include <vector>
#include "link.h"
using namespace std;

class Download : public Ability {
    Player *activePlayer; // player that owns the ability
    vector<vector<Cell>> *grid; // pass in grid of the board
    Link *targetLink;
public:
    Download(Type type, Player *activePlayer, vector<vector<Cell>> *grid);
    void apply() override; // passes in enemy link
    bool checkValid() override;
    char getType() override;
    void setTarget(Link *target);
};

#endif
