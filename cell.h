#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
#include "link.h"

class Cell {
    vector<Observer *> observers;
    int row;
    int col;
    bool isFirewall; // check if cell is a Firewall or not
    bool isServerPort; // check if cell is a server port or not
    Link *link; // ptr to specific link

public:
    Cell(int row, int col, bool isFirewall, bool isServerPort, Link *link);
    int getRow();
    int getCol();
    void setCoords(int r, int c);
    void notifyObservers();
    void attach(Observer *o);
    bool getIsFirewall();
    bool getIsServerPort();
    void setLinkNull();
    Link* getLink();
    void setLink(Link *newlink);

    // add any more fields as necessary
};

#endif
