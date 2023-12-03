#include "cell.h"
using namespace std;

Cell::Cell(): isFirewall{false}, isServerPort{false}, link{nullptr}{}

int Cell::getRow() {
    return row;
}
    
int Cell::getCol() {
    return col;
}

void Cell::notifyObservers() {
    for (auto obs : observers) {
        obs->notify(*this);
    }
}

void Cell::attach(Observer *o) {
    observers.emplace_back(o);
}

bool Cell::getIsFirewall() {
    return isFirewall;
}
   
bool Cell::getIsServerPort() {
    return isServerPort;
}

// Also implemented setting isServerPort and isFirewall to false
void Cell::setLinkNull() {
    link = nullptr;
    // isServerPort = false;
    // isFirewall = false;
}

Link* Cell::getLink() {
    return link;
}

void Cell::setLink(Link *newlink) {
    link = newlink;
}

void Cell::setIsServerPortTrue() {
    isServerPort = true;
}

void Cell::setCoords(int r, int c) {
    row = r;
    col = c;
}

void Cell::setFirewall() {
    isFirewall = true;
}

// === Firewall Logic ====
void Cell::setFirewallOwner(Player *player) {
    firewallOwner = player;
}

Player *Cell::getFirewallOwner() {
    return firewallOwner;
}
