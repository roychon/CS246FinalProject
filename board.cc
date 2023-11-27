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

        else if (player.hasLinkAt(x + linkxcoord, y + linkycoord)) {
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

        else if (player.hasLinkAt(x + linkxcoord, y + linkycoord)) {
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
    if (NonActivePlayer->hasLinkAt(x, y)) {
        return true;
    }
    else {
        return false;
    }
}

void Board::battle(Player &ActivePlayer, Player &NonActivePlayer, Link &ActivePlayerLink, Link &NonActivePlayerLink) {
    if (ActivePlayerLink.getStrength() >= NonActivePlayerLink.getStrength()) {
        if (NonActivePlayerLink.getType() == "D") {
            ActivePlayer.changeDataCount();
        }
        else {
            ActivePlayer.changeVirusCount();
        }
        NonActivePlayerLink.setX(-1);
        NonActivePlayerLink.setY(-1);
        NonActivePlayerLink.revealLink();
        ActivePlayerLink.revealLink();
        grid[NonActivePlayerLink.getY()][NonActivePlayerLink.getX()].setLinkNull();
        td->notify(grid[NonActivePlayerLink.getY()][NonActivePlayerLink.getX()]);
    }

    else {
        if (ActivePlayerLink.getType() == "D") {
            NonActivePlayer.changeDataCount();
        }
        else {
            NonActivePlayer.changeVirusCount();
        }
        ActivePlayerLink.setX(-1);
        ActivePlayerLink.setY(-1);
        NonActivePlayerLink.revealLink();
        ActivePlayerLink.revealLink();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        td->notify(grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()]);
    }
}

    void Board::move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int x, int y) {
        int linkxcoord = link.getX();
        int linkycoord = link.getY();

        if (grid[linkycoord + y][linkxcoord + x].getIsServerPort()) {
            if (link.getType() == "D") {
                NonActivePlayer->changeDataCount();
            }
            else {
                NonActivePlayer->changeVirusCount();
            }
            link.setX(-1);
            link.setY(-1);
            link.revealLink();
            grid[linkycoord + y][linkxcoord + x].setLinkNull();
            td->notify(grid[linkycoord + y][linkxcoord + x]);
        }

        else {
            grid[linkycoord + y][linkxcoord + x].setLink(&link);
            grid[linkycoord][linkxcoord].setLinkNull();
        }
    }

void Board::printTextDisplay() {
    cout << *td;
}
