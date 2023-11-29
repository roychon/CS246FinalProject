#include <iostream>
#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay() : gridSize{8} {
    // currently just initializing board with "."
    // when board init feature is added, this constructor will change too.
    for (int i = 0; i < gridSize; ++i) {
        grid.emplace_back(gridSize, '.');
    }
}

void TextDisplay::notify(Cell &c) {
    // nullptr means no link is present
    // will need to check for firewall later (within nullptr if statement)
    if (c.getIsServerPort()) {
        grid[c.getRow()][c.getCol()] = 'S';
    }

    else if (c.getLink() == nullptr) {
        grid[c.getRow()][c.getCol()] = '.';
    }

    else grid[c.getRow()][c.getCol()] = c.getLink()->getId();
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  cout << "========" << endl;
  for (const auto &inner: td.grid) {
      for (const char cell : inner) {
        out << cell;
      }
      out << endl;
  }
  cout << "========" << endl;
  return out;
}
