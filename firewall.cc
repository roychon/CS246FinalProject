#include "firewall.h"

Firewall::Firewall(Player *firewallOwner, vector<vector<Cell>> *grid): Ability(Type::Firewall), grid{grid}, firewallOwner(firewallOwner) {}

void Firewall::apply(int x, int y) {
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[y][x];
        cell.setFirewallOwner(firewallOwner);
        cell.notifyObservers();
        isUsed = true;
    } else {
        cout << "abiltiy failed" << endl;
    }
}

bool Firewall::checkValid(int x, int y) {
    Cell &cell = (*grid)[y][x];
    if (cell.getFirewallOwner() != nullptr || cell.getLink() != nullptr) return false;
    return true;
}

char Firewall::getType() {
    return 'F';
}
