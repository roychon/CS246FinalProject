#include "cell.h"
using namespace std;

Cell::Cell(int row, int col, bool isFirewall, bool isServerPort, Link *link) : row{row}, col{col}, 
isFirewall{isFirewall}, isServerPort{isServerPort}, link{link} {
    vector<Observer *> newobs;
    observers = newobs;
}

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
    isServerPort = false;
    isFirewall = false;
}

Link* Cell::getLink() {
    return link;
}

void Cell::setLink(Link *newlink) {
    link = newlink;
}
