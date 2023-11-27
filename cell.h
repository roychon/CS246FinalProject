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
    int getRow();
    int getCol();
    void notifyObservers();
    void attach(Observer *o);
    bool GetIsFirewall();
    bool GetIsServerPort();
    void SetLinkNull();
    Link* GetLink();
    void SetLink(Link *link);

    // add any more fields as necessary
};

#endif
