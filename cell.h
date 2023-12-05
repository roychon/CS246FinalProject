#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include "observer.h"
#include "link.h"
#include "player.h"
using namespace std;

class Link;
class Player;

class Cell {
    vector<Observer *> observers;
    int row;
    int col;
    Link *link; // ptr to specific link
    Player *firewallOwner;

public:
    Cell();
    int getRow();
    int getCol();
    void notifyObservers();
    void attach(Observer *o);
    Link* getLink();
    void setLinkNull(); // Sets a cell's contents to null
    void setCoords(int r, int c); // Set's a cell's coordinates
    void setLink(Link *newlink); // Set's a cell's contents to a Link
    void setFirewallOwner(Player *); // Set's a firewall owner
    Player *getFirewallOwner();
};

#endif
