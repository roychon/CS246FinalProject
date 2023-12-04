#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &xw) : xw{xw}, enhancementsOn{false} {
    xw.fillRectangle(0, 0, 500, 500, 0);
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8, '.');
    }
    for (int j = 0; j < 8; ++j) {
        for (int k = 0; k < 8; ++k) {
            xw.drawString(((k * 500) / 8) + 25, ((j * 350) / 8) + 100, ".");
        }
    }
}

void GraphicsDisplay::notify(Cell &c) {
    // nullptr means no link is present
    // will need to check for firewall later (within nullptr if statement)

    if (c.getLink() != nullptr && (c.getLink()->getType() != 'S')) {
        grid[c.getRow()][c.getCol()] = c.getLink()->getId();
        string convert{c.getLink()->getId()};        
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 350) / 8) + 85, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 350) / 8) + 100, convert);
    }

    else if (c.getFirewallOwner() != nullptr) {
        if (c.getFirewallOwner()->getplayerID() == 1) {
            grid[c.getRow()][c.getCol()] = 'm'; // need to account for lower case too
            xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 350) / 8) + 85, 25, 25, 0);
            xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 350) / 8) + 100, "m");
        }

        else if (c.getFirewallOwner()->getplayerID() == 2) {
            grid[c.getRow()][c.getCol()] = 'w'; // need to account for lower case too
            xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 350) / 8) + 85, 25, 25, 0);
            xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 350) / 8) + 100, "w");
        }
    }

    else if (c.getLink() == nullptr) {
        grid[c.getRow()][c.getCol()] = '.';
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 350) / 8) + 85, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 350) / 8) + 100, ".");
    }

    else if (c.getLink()->getType() == 'S') {
        grid[c.getRow()][c.getCol()] = 'S';
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 350) / 8) + 85, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 350) / 8) + 100, "S");
    }
}

void GraphicsDisplay::playerDisplays(Player *activePlayer, Player *nonActivePlayer) {
    xw.fillRectangle(0, 0, 500, 85, 0);
    xw.fillRectangle(0, 415, 500, 85, 0);
    Player* Player1 = nullptr;
    Player* Player2 = nullptr;
    if (activePlayer->getplayerID() == 1) {
        Player1 = activePlayer;
        Player2 = nonActivePlayer;
    }
    else {
        Player2 = activePlayer;
        Player1 = nonActivePlayer;
    }

    // Player 1 Display
    xw.drawString(10, 20, "Player 1:");
    xw.drawString(175, 20, "Downloaded:");
    xw.fillRectangle(245, 11, 12, 10, 3);
    xw.drawString(245, 20, to_string(Player1->getDataCount()));
    xw.drawString(252, 20, "D,");
    xw.fillRectangle(270, 11, 12, 10, 2);
    xw.drawString(270, 20, to_string(Player1->getVirusCount()));
    xw.drawString(277, 20, "V");
    xw.drawString(380, 20, "Abilities:");
    xw.drawString(445, 20, to_string(Player1->getNumAbilitiesLeft()));
    vector<string> player1links;
    for (auto link : Player1->getLinks()) {
        string strcnv;
        if (Player1 == activePlayer || link->getIsRevealed() == 1) {
            string intcnv = to_string(link->getStrength());
            strcnv = link->getType() + intcnv;
            player1links.emplace_back(strcnv);
        }
        else {
            player1links.emplace_back("?");
        }
    }
    char c = 'a';
    for (int j = 0; j < 8; ++j) {
        string strcnv;
        strcnv = (c + j);
        strcnv = strcnv + ":";
        xw.drawString(((j * 60) + 15), 55, strcnv);
        if (player1links[j][0] == 'D') {
            xw.fillRectangle(((j * 60) + 30), 45, 12, 10, 3);
        }
        else if (player1links[j][0] == 'V') {
            xw.fillRectangle(((j * 60) + 30), 45, 12, 10, 2);
        }
        xw.drawString(((j * 60) + 30), 55, player1links[j]);
    }

    // Player 2 Display
    xw.drawString(10, 435, "Player 2:");
    xw.drawString(175, 435, "Downloaded:");
    xw.fillRectangle(245, 426, 12, 10, 3);
    xw.drawString(245, 435, to_string(Player2->getDataCount()));
    xw.drawString(252, 435, "D,");
    xw.fillRectangle(270, 426, 12, 10, 2);
    xw.drawString(270, 435, to_string(Player2->getVirusCount()));
    xw.drawString(277, 435, "V");
    xw.drawString(380, 435, "Abilities:");
    xw.drawString(445, 435, to_string(Player2->getNumAbilitiesLeft()));
    vector<string> player2links;
    for (auto link : Player2->getLinks()) {
        string strcnv;
        if (Player2 == activePlayer || link->getIsRevealed() == 1) {
            string intcnv = to_string(link->getStrength());
            strcnv = link->getType() + intcnv;
            player2links.emplace_back(strcnv);
        }
        else {
            player2links.emplace_back("?");
        }
    }
    char p = 'A';
    for (int k = 0; k < 8; ++k) {
        string strcnv;
        strcnv = (p + k);
        strcnv = strcnv + ":";
        xw.drawString(((k * 60) + 15), 470, strcnv);
        if (player2links[k][0] == 'D') {
            xw.fillRectangle(((k * 60) + 30), 460, 12, 10, 3);
        }
        else if (player2links[k][0] == 'V') {
            xw.fillRectangle(((k * 60) + 30), 460, 12, 10, 2);
        }
        xw.drawString(((k * 60) + 30), 470, player2links[k]);
    }
}

void GraphicsDisplay::toggleEnhancementsOn() {
    enhancementsOn = !enhancementsOn;
}

GraphicsDisplay::~GraphicsDisplay() {}
