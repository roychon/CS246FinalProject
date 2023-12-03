#include "poweraugment.h"

PowerAugment::PowerAugment(Player *activePlayer, vector<vector<Cell>> *grid) : Ability(), grid{grid}, activePlayer{activePlayer} {}

void PowerAugment::apply(int x, int y) {
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[y][x];
        cell.getLink()->augmentpower();
        cell.notifyObservers();
        isUsed = true;
    } else {
        cout << "ability failed" << endl;
    }
}

bool PowerAugment::checkValid(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (&link->getPlayer() == activePlayer) {
        return true;
    }
    
    return false;
}

char PowerAugment::getType() {
    return 'A';
}
