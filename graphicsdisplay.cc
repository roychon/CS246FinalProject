#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(Xwindow &xw) : xw{xw}, enhancementsOn{false} {
    xw.fillRectangle(0, 0, 500, 500, 0);
    for (int i = 0; i < 8; ++i) {
        grid.emplace_back(8, '.');
    }
    for (int j = 0; j < 8; ++j) {
        for (int k = 0; k < 8; ++k) {
            xw.drawString(((k * 500) / 8) + 25, ((j * 500) / 8) + 25, ".");
        }
    }
}

void GraphicsDisplay::notify(Cell &c) {
    // nullptr means no link is present
    // will need to check for firewall later (within nullptr if statement)
    if (c.getIsServerPort()) {
        grid[c.getRow()][c.getCol()] = 'S';
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 500) / 8) + 10, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 500) / 8) + 25, "S");
    } else if(c.getIsFirewall()) {
        grid[c.getRow()][c.getCol()] = 'M'; // need to account for lower case too
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 500) / 8) + 10, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 500) / 8) + 25, "M");
    }

    else if (c.getLink() == nullptr) {
        grid[c.getRow()][c.getCol()] = '.';
        xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 500) / 8) + 10, 25, 25, 0);
        xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 500) / 8) + 25, ".");
    }

    else {
    grid[c.getRow()][c.getCol()] = c.getLink()->getId();
    string convert{c.getLink()->getId()};        
    xw.fillRectangle(((c.getCol() * 500) / 8) + 10, ((c.getRow() * 500) / 8) + 10, 25, 25, 0);
    xw.drawString(((c.getCol() * 500) / 8) + 25, ((c.getRow() * 500) / 8) + 25, convert);
    }
}

void GraphicsDisplay::setActivePlayer(Player *player) {
    activePlayer = player;
}

void GraphicsDisplay::toggleenhancementsOn() {
    if (enhancementsOn == true) {
        enhancementsOn = false;
    }
    else {
        enhancementsOn = true;
    }
}

GraphicsDisplay::~GraphicsDisplay() {}
