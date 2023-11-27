#ifndef __BOARD_H__
#define __BOARD_H__
#include "cell.h"
#include "textdisplay.h"
#include "link.h"

class Board {
    int size;
    vector<vector<Cell>> grid;
    std::unique_ptr<TextDisplay> td;
    // GraphicsDisplay *gd;

public:
    Board(vector<vector<Cell>> grid);
    bool isInvalidMove(Link &link, int x, int y, Player &player);
    bool isOccupiedByOpponent(Player *NonActivePlayer, int x, int y);
    void battle(Player &ActivePlayer, Player &NonActivePlayer, Link &ActivePlayerLink, Link &NonActivePlayerLink);
    void move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int x, int y);
    void printTextDisplay();
    void setup();

    // add any more fields as necessary
};

#endif
