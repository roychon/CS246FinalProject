#include "firewall.h"

Firewall::Firewall(vector<vector<Cell>> *grid, int id): Ability{id}, grid{grid} {}

void Firewall::apply(Link &link) {
    (*grid)[link.getY()][link.getX()].setFirewall();
}
