#include "board.h"
using namespace std;

Board::Board() : size{8}, td{make_unique<TextDisplay>()} {}

// Handle board orientation of commands in the main function
// Therefore a positive y value means moving upwards on the board display
// And a positive x value means moving to the right on the board display

bool Board::isInvalidMove(Link &link, int xCord, int yCord, Player &player) {

    if (player.getPlayerID() == 2) {
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
            ActivePlayer.incrementDataCount();
        }
        else {
            ActivePlayer.incrementVirusCount();
        }
        grid[NonActivePlayerLink.getY()][NonActivePlayerLink.getX()].setLink(&ActivePlayerLink);
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        ActivePlayerLink.setX(NonActivePlayerLink.getX());
        ActivePlayerLink.setY(NonActivePlayerLink.getY());
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        NonActivePlayerLink.setX(-1);
        NonActivePlayerLink.setY(-1);
        NonActivePlayerLink.revealLink();
        ActivePlayerLink.revealLink();
    }   

    else {
        if (ActivePlayerLink.getType() == "D") {
            NonActivePlayer.incrementDataCount();
        }
        else {
            NonActivePlayer.incrementVirusCount();
        }
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        ActivePlayerLink.setX(-1);
        ActivePlayerLink.setY(-1);
        ActivePlayerLink.revealLink();
        NonActivePlayerLink.revealLink();
    }
}


void Board::move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int xCord, int yCord) {
    
    if (yCord > 7 || yCord < 0) {
        grid[link.getY()][link.getX()].setLinkNull();
        grid[link.getY()][link.getX()].notifyObservers();
        link.setX(-1);
        link.setY(-1);
        if (link.getType() == "D") {
            ActivePlayer->incrementDataCount();
        }
        else {
            ActivePlayer->incrementVirusCount();
        }
    }

    else if (grid[yCord][xCord].getIsServerPort()) {
        if (link.getType() == "D") {
            NonActivePlayer->incrementDataCount();
        }
        else {
            NonActivePlayer->incrementVirusCount();
        }
        grid[link.getY()][link.getX()].setLinkNull();
        grid[link.getY()][link.getX()].notifyObservers();
        link.setX(-1);
        link.setY(-1);
        link.revealLink();
    }

    else {
        grid[yCord][xCord].setLink(&link);
        grid[link.getY()][link.getX()].setLinkNull();
        grid[link.getY()][link.getX()].notifyObservers();
        link.setX(xCord);
        link.setY(yCord);
        grid[yCord][xCord].notifyObservers();
    }
}

void Board::updateDisplayPOV(Player *activePlayer) {
    td->setActivePlayer(activePlayer);
}

void Board::printTextDisplay() {
    cout << *td;
}

// ===================== Board Setup =======================

// sets the observers and coords for every cell.
void Board::setCellObservers() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Cell &current = grid[i][j];
            current.setCoords(i, j);
            current.attach(td.get()); // get and pass raw ptr
        }
    }   
}

void Board::setup() {
    // create cells
    for (int i = 0; i < size; ++i) {
        grid.emplace_back();
        for (int j = 0; j < size; ++j) {
            grid[i].emplace_back();
        }
    }
    // set cell observers
    setCellObservers();
}

void Board::setupLinks(Player &player) {
    vector<Link*> playerLinks = player.getLinks();
    int frontRow = 1;
    int backRow = 0;
    if (player.getPlayerID() == 2) {
        frontRow = 6;
        backRow = 7;
    }
    for (int i = 0; i < size; ++i) {
        // server port row:
        if (i == 3 || i == 4) {
            grid[backRow][i].setIsServerPortTrue();
            grid[frontRow][i].setLink(playerLinks[i]);
            playerLinks[i]->setX(i);
            playerLinks[i]->setY(frontRow);
            grid[frontRow][i].notifyObservers();
        }
        else {
            grid[backRow][i].setLink(playerLinks[i]);
            playerLinks[i]->setX(i);
            playerLinks[i]->setY(backRow);
        }
            grid[backRow][i].notifyObservers();
    }

    // hardcoding stats for now
    for (int i = 0; i < size; ++i) {
        playerLinks[i]->setStrength(i + 1);
        playerLinks[i]->setType("D");
        if (i > 3) {
            playerLinks[i]->setStrength(i - 3);
            playerLinks[i]->setType("V");     
        }
    }
}
