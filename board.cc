#include "board.h"
#include "cell.h"
using namespace std;

Board::Board(vector<vector<Cell>> grid, TextDisplay *td) : size{8}, grid{grid}, td{td} {}

// Handle board orientation of commands in the main function
// Therefore a positive y value means moving upwards on the board display
// And a positive x value means moving to the right on the board display
bool Board::isInvalidMove(Link &link, int x, int y, Player &player) {
    int linkxcoord = link.getX();
    int linkycoord = link.getY();

    if (player.getplayerID() == 2) {
        if (x + linkxcoord > 7 || x + linkxcoord < 0 || y + linkycoord > 7) {
            return true;
        }

        else if (player.HasLinkAt(x + linkxcoord, y + linkycoord)) {
            return true;
        }

        else if ((x + linkxcoord == 3 && y + linkycoord == 7) || (x + linkxcoord == 4 && y + linkycoord == 7)) {
            return true;
        }

        else {
            return false;
        }
    }

    else {
        if (x + linkxcoord > 7 || x + linkxcoord < 0 || y + linkycoord < 0) {
            return true;
        }

        else if (player.HasLinkAt(x + linkxcoord, y + linkycoord)) {
            return true;
        }

        else if ((x + linkxcoord == 3 && y + linkycoord == 0) || (x + linkxcoord == 4 && y + linkycoord == 0)) {
            return true;
        }
        
        else {
            return false;
        }
}
}

bool Board::isOccupiedByOpponent(Player *NonActivePlayer, int x, int y) {
    if (NonActivePlayer->HasLinkAt(x, y)) {
        return true;
    }
    else {
        return false;
    }
}

void Board::battle(Link &link1, Link &link2) {}
