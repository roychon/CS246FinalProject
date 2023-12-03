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
    bool isFirewall; // check if cell is a Firewall or not
    bool isServerPort; // check if cell is a server port or not
    Link *link; // ptr to specific link
    Player *firewallOwner;

public:
    Cell();
    int getRow();
    int getCol();
    void notifyObservers();
    void attach(Observer *o);
    bool getIsFirewall();
    bool getIsServerPort();
    Link* getLink();
    void setLinkNull();
    void setCoords(int r, int c);
    void setLink(Link *newlink);
    void setIsServerPortTrue();
    void setFirewall();
    void setFirewallOwner(Player *);
    Player *getFirewallOwner();

    // add any more fields as necessary
};

#endif
