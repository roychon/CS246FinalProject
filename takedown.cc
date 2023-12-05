#include "takedown.h"

Takedown::Takedown(Player* activePlayer, vector<vector<Cell>> *grid): Ability(), activePlayer{activePlayer}, grid{grid} {}

void Takedown::apply(int x, int y) {
    if (checkValid(x,y) == true) {
        Link *link = (*grid)[y][x].getLink();
        link->incrementMoveFactor(-1 * link->getMoveFactor());
        (*grid)[y][x].notifyObservers();
        isUsed = true;
    } 
    else {
        throw(logic_error("Cannot use Takedown on that.\n"));
    }
}

bool Takedown::checkValid(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (&link->getPlayer() == activePlayer) {
        return false;
    }
    
    return true;
}

char Takedown::getType() {
    return 'T';
}
