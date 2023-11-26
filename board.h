#ifndef __BOARD_H__
#define __BOARD_H__
#include "textdisplay.h"
#include "link.h"

class Board {
    int size;
    vector<vector<Cell>> grid;
    TextDisplay *td;
    // GraphicsDisplay *gd;

public:
    bool isInvalidMove(Link &link, int x, int y, Player &player);
    bool isOccupiedByOpponent(Link &link, int x, int y);
    void battle(Link &link1, Link &link2);
    void move(Link &link, int x, int y);

    // add any more fields as necessary
};

#endif
