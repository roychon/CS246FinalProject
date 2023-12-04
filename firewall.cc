#include "firewall.h"

Firewall::Firewall(Player *firewallOwner, vector<vector<Cell>> *grid): Ability(), grid{grid}, firewallOwner(firewallOwner) {}

void Firewall::apply(int x, int y) {
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[y][x];
        cell.setFirewallOwner(firewallOwner);
        cell.notifyObservers();
        isUsed = true;
    } else {
        throw(logic_error("Cannot use Firewall on that square.\n"));
    }
}

bool Firewall::checkValid(int x, int y) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return false;
    Cell &cell = (*grid)[y][x];
    if (cell.getFirewallOwner() != nullptr || cell.getLink() != nullptr) return false;
    return true;
}

char Firewall::getType() {
    return 'F';
}
