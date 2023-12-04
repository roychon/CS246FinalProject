#include "board.h"
#include <sstream>
#include <random>
#include <algorithm>
using namespace std;

Board::Board(Xwindow &xw) : size{8}, td{make_unique<TextDisplay>()}, gd{make_unique<GraphicsDisplay>(xw)}, enhancementsOn{false} {}

Board::Board() : size{8}, td{make_unique<TextDisplay>()}, gd{nullptr}, enhancementsOn{false} {}

// Handle board orientation of commands in the main function
// Therefore a positive y value means moving upwards on the board display
// And a positive x value means moving to the right on the board display
bool Board::isInvalidMove(Link &link, int xCord, int yCord, Player &player) {
    if (player.getplayerID() == 1 && (xCord > 7 || xCord < 0 || yCord < 0)) return true;
    else if (player.getplayerID() == 2 && (xCord > 7 || xCord < 0 || yCord > 7)) return true;
    // player is trying to move onto their own link (or server)
    if (player.hasLinkAt(xCord, yCord)) {
        return true;
    }
    else {
        return false;
    }
}

bool Board::opponentHasFireWallAt(int xCord, int yCord, Player *opponent) {
    if (yCord > 7 || yCord < 0) return false;
    else return (grid[yCord][xCord].getFirewallOwner() == opponent) ? true : false;
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
    if (opponentHasFireWallAt(NonActivePlayerLink.getX(), NonActivePlayerLink.getY(), &NonActivePlayer)) {
        ActivePlayerLink.revealLink();
        if (ActivePlayerLink.getType() == 'V') { 
            ActivePlayer.incrementDownloads('V');
            Cell &cellToBeDeleted = grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()];
            cellToBeDeleted.setLinkNull();
            cellToBeDeleted.notifyObservers();
            ActivePlayerLink.setX(-1);
            ActivePlayerLink.setX(-1);
            ActivePlayerLink.setIsDead();
            return;
        }
    }

    // if server port, download immediately
    if (NonActivePlayerLink.getType() == 'S') {
        NonActivePlayer.incrementDownloads(ActivePlayerLink.getType());
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        ActivePlayerLink.setX(-1);
        ActivePlayerLink.setY(-1);
        ActivePlayerLink.revealLink();
        ActivePlayerLink.setIsDead();
    } 
    
    else if (ActivePlayerLink.getStrength() >= NonActivePlayerLink.getStrength()) {
        ActivePlayer.incrementDownloads(NonActivePlayerLink.getType());
        grid[NonActivePlayerLink.getY()][NonActivePlayerLink.getX()].setLink(&ActivePlayerLink);
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        ActivePlayerLink.setX(NonActivePlayerLink.getX());
        ActivePlayerLink.setY(NonActivePlayerLink.getY());
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        NonActivePlayerLink.setX(-1);
        NonActivePlayerLink.setY(-1);
        NonActivePlayerLink.setIsDead();
        NonActivePlayerLink.revealLink();
        ActivePlayerLink.revealLink();
    } else {
        NonActivePlayer.incrementDownloads(ActivePlayerLink.getType());
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].setLinkNull();
        grid[ActivePlayerLink.getY()][ActivePlayerLink.getX()].notifyObservers();
        ActivePlayerLink.setX(-1);
        ActivePlayerLink.setY(-1);
        ActivePlayerLink.setIsDead();
        ActivePlayerLink.revealLink();
        NonActivePlayerLink.revealLink();
    }
}


void Board::move(Player* ActivePlayer, Player* NonActivePlayer, Link &link, int xCord, int yCord) {
    if (opponentHasFireWallAt(xCord, yCord, NonActivePlayer)) {
        link.revealLink();
        if (link.getType() == 'V') { 
            ActivePlayer->incrementDownloads('V');
            Cell &cellToBeDeleted = grid[link.getY()][link.getX()];
            cellToBeDeleted.setLinkNull();
            cellToBeDeleted.notifyObservers();
        }
        else
        {
            grid[link.getY()][link.getX()].setLinkNull();
            grid[link.getY()][link.getX()].notifyObservers();
            link.setX(xCord);
            link.setY(yCord);
            grid[yCord][xCord].setLink(&link);
            grid[yCord][xCord].notifyObservers();
        }
    }
    
    else if (yCord > 7 || yCord < 0) {
        grid[link.getY()][link.getX()].setLinkNull();
        grid[link.getY()][link.getX()].notifyObservers();
        link.setX(-1);
        link.setY(-1);
        link.setIsDead();
        ActivePlayer->incrementDownloads(link.getType());
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
            if (gd != nullptr) {
            current.attach(gd.get());
            }
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

bool Board::vecContains(vector<int> vec, int item) {
    for (int check : vec) {
        if (check == item) {
            return true;
        }
    }
    return false;
}

void Board::setupLinks(Player &player, string playerlinks) {
    vector<Link*> playerLinks = player.getLinks();
    vector<Link*> playerServers = player.getServerPorts();
    int frontRow = 1;
    int backRow = 0;
    if (player.getplayerID() == 2) {
        frontRow = 6;
        backRow = 7;
    }
    for (int i = 0; i < size; ++i) {
        // server port row:
        if (i == 3 || i == 4) {
            // set server port (this array is only length 2)
            grid[backRow][i].setLink(playerServers[i - 3]);
            playerServers[i - 3]->setX(i);
            playerServers[i - 3]->setY(backRow);
            // set link
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

    if (playerlinks != "Default") {
    istringstream links{playerlinks};
    for (int i = 0; i < size; ++i) {
        char typechar;
        links >> typechar;
        int str;
        links >> str;
        playerLinks[i]->setStrength(str);
        playerLinks[i]->setType(typechar);
    }}

    else {
        vector<int> positions = {0, 1, 2, 3, 4, 5, 6, 7};
        vector<int> strengths = {1, 2, 3, 4};
        vector<int> used = {};
        if (player.getplayerID() == 1) {
        srand(time(NULL));
        }
        else {
        srand(time(NULL) * 1000);
        }
    
        for (int str : strengths) {

        // adding the data for this strength
        int randnum = rand() % 8;
        while (vecContains(used, randnum)) {
            randnum = rand() % 8;
        }
        playerLinks[randnum]->setStrength(str);
        playerLinks[randnum]->setType('D');
        used.emplace_back(randnum);

        // adding the virus for this strength
        int randnum2 = rand() % 8;
        while (vecContains(used, randnum2)) {
            randnum2 = rand() % 8;
        }
        playerLinks[randnum2]->setStrength(str);
        playerLinks[randnum2]->setType('V');
        used.emplace_back(randnum2);
        }
    }
}

void Board::toggleEnhancementsOn() {
    if (enhancementsOn == true) {
        enhancementsOn = false;
        td.get()->toggleEnhancementsOn();
    }
    else {
        enhancementsOn = true;
        td.get()->toggleEnhancementsOn();
    }
}

vector<vector<Cell>>* Board::getGrid() {
    return &grid;
}

GraphicsDisplay* Board::getGD() {
    return gd.get();
}
