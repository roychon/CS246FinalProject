#include "firewall.h"

Firewall::Firewall(vector<vector<Cell>> *grid): Ability{}, grid{grid} {}

void Firewall::apply(int x, int y) {
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[x][y];
        cell.setFirewall();
        cell.notifyObservers();
    } else {
        cout << "abiltiy failed" << endl;
    }
}

bool Firewall::checkValid(int x, int y) {
    Cell &cell = (*grid)[x][y];
    if (cell.getIsFirewall() || cell.getIsServerPort() || cell.getLink() != nullptr) return false;
    return true;
}
