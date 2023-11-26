#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
#include "link.h"

class Cell {
    vector<Observer *> observers;
    bool isFirewall; // check if cell is a Firewall or not
    Link *link; // ptr to specific link

public:
    void notifyObservers();
    void attach(Observer *o);
    bool isFirewall();

    // add any more fields as necessary
};

#endif
