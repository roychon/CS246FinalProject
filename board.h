#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include "cell.h"
#include "textdisplay.h"
#include "link.h"
using namespace std;

class Board {
    int size;
    vector<vector<Cell>> grid;
    unique_ptr<TextDisplay> td;
    // GraphicsDisplay *gd;
    void setCellObservers();

public:
    Board();
    bool isInvalidMove(Link &link, int x, int y, Player &player);
    bool isOccupiedByOpponent(Player *NonActivePlayer, int xCord, int yCord);
    void battle(Player &ActivePlayer, Player &NonActivePlayer, Link &ActivePlayerLink, Link &NonActivePlayerLink);
    void move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int x, int y);
    void updateDisplayPOV(Player *activePlayer);
    void printTextDisplay();
    void setup();
    void setupLinks(Player &player, string playerlinks);

    // add any more fields as necessary
};

#endif
