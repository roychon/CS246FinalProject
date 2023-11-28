#include "board.h"
#include "cell.h"
using namespace std;

Board::Board(vector<vector<Cell>> grid, TextDisplay *td) : size{8}, grid{grid}, td{td} {}

// Handle board orientation of commands in the main function
// Therefore a positive y value means moving upwards on the board display
// And a positive x value means moving to the right on the board display

bool Board::isInvalidMove(Link &link, int xCord, int yCord, Player &player) {
    int linkxcoord = link.getX();
    int linkycoord = link.getY();

    if (player.getplayerID() == 2) {
        // check out of bounds
        if (xCord > 7 || xCord < 0 || yCord > 7) {
            return true;
        }
        // player is trying to move onto their own link
        else if (player.hasLinkAt(xCord, yCord)) {
            return true;
        }
        // player trying to move onto server port
        else if (yCord == 7 && (xCord == 3 || xCord == 4)) {
            return true;
        }
        // valid move
        else {
            return false;
        }
    }

    else {

        // Player 1 : top of the board
        if (xCord > 7 || xCord < 0 || yCord < 0) {
            return true;
        }
         else if (player.hasLinkAt(xCord, yCord)) {
            return true;
        }
         else if (yCord == 0 && (xCord == 3 || xCord == 4)) {
            return true;
        }
        else {
            return false;
        }
}
}

// xCord, yCord are coordinates it needs to move into
bool Board::isOccupiedByOpponent(Player *NonActivePlayer, int xCord, int yCord) {
    if (NonActivePlayer->hasLinkAt(xCord, yCord)) {
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
        grid[NonActivePlayerLink.getY()][NonActivePlayerLink.getX()].notifyObservers();
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
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
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
            grid[linkycoord + y][linkxcoord + x].notifyObservers();
        }

        else {
            grid[linkycoord + y][linkxcoord + x].setLink(&link);
            grid[linkycoord][linkxcoord].setLinkNull();
            grid[linkycoord + y][linkxcoord + x].notifyObservers();
            grid[linkycoord][linkxcoord].notifyObservers();
        }
}

void Board::printTextDisplay() {
    cout << *td;
}
