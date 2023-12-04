#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay() : gridSize{8}, enhancementsOn{false} {
    // currently just initializing board with "."
    // when board init feature is added, this constructor will change too.
    for (int i = 0; i < gridSize; ++i) {
        grid.emplace_back(gridSize, '.');
    }
}

void TextDisplay::notify(Cell &c) {
    if (c.getLink()) {
        grid[c.getRow()][c.getCol()] = c.getLink()->getId();
    } else if (c.getFirewallOwner() != nullptr) {
        grid[c.getRow()][c.getCol()] = (c.getFirewallOwner()->getplayerID() == 1 ? 'm' : 'w');
    } else {
        grid[c.getRow()][c.getCol()] = '.';
    }
}

void TextDisplay::setActivePlayer(Player *player) {
    activePlayer = player;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  cout << "========" << endl;
  Player *activePlayer = td.activePlayer;

  if (td.enhancementsOn == true) {
  if (activePlayer->getplayerID() == 1) {
    for (int i = td.gridSize - 1; i >= 0; --i) {
        for (int j = td.gridSize - 1; j >= 0; --j) {
            out << td.grid[i][j];
        }
        out << endl;
    }
  } else if (activePlayer->getplayerID() == 2) {
    for (const auto &inner: td.grid) {
        for (const char cell : inner) {
            out << cell;
        }
        out << endl;
    }
  }}

  else {
    for (const auto &inner: td.grid) {
        for (const char cell : inner) {
            out << cell;
        }
        out << endl;
    }
  }

  cout << "========" << endl;
  return out;
}

void TextDisplay::toggleEnhancementsOn() {
    if (enhancementsOn == true) {
        enhancementsOn = false;
    }
    else {
        enhancementsOn = true;
    }
}
