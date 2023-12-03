#include "firewall.h"

Firewall::Firewall(Player *firewallOwner, vector<vector<Cell>> *grid): Ability(Type::Firewall), grid{grid}, firewallOwner(firewallOwner) {}

void Firewall::apply() {
    if (checkValid(targetX, targetY)) {
        Cell &cell = (*grid)[targetY][targetX];
        cell.setFirewallOwner(firewallOwner);
        cell.notifyObservers();
        isUsed = true;
    } else {
        cout << "abiltiy failed" << endl;
    }
}

bool Firewall::checkValid() {
    Cell &cell = (*grid)[targetY][targetX];
    if (cell.getFirewallOwner() != nullptr || cell.getLink() != nullptr) return false;
    return true;
}

char Firewall::getType() {
    return 'F';
}

void Firewall::setTargetCoord(int x, int y) {
    targetX = x;
    targetY = y;
}
