#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include "cell.h"
#include "textdisplay.h"
#include "link.h"
#include "graphicsdisplay.h"
#include "window.h"
using namespace std;

class Board {
    int size;
    vector<vector<Cell>> grid;
    unique_ptr<TextDisplay> td;
    unique_ptr<GraphicsDisplay> gd;
    void setCellObservers();
    bool enhancementsOn;
    bool vecContains(vector<int> vec, int item);

public:
    Board(Xwindow *xw);
    Board();
    bool isInvalidMove(Link &link, int x, int y, Player &player); // Checks if a move is valid
    bool isOccupiedByOpponent(Player *NonActivePlayer, int xCord, int yCord); // Checks if the target cell is occupied by an opponent "link"
    void battle(Player &ActivePlayer, Player &NonActivePlayer, Link &ActivePlayerLink, Link &NonActivePlayerLink); // Performs battle logic
    void move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int x, int y); // Moves a link to the target x, y
    void updateDisplayPOV(Player *activePlayer);
    void printTextDisplay();
    void setup(); // Prepares the board cells
    void setupLinks(Player &player, string playerlinks); // Places links in the cells and sets up their locations
    void toggleEnhancementsOn();
    vector<vector<Cell>>* getGrid();
    GraphicsDisplay* getGD();
    bool opponentHasFireWallAt(int xCord, int yCord, Player *opponent); // Checks if an opponent has a firewall at a given coordinate
};

#endif
