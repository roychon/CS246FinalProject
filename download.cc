#include "download.h"

Download::Download(Player *player, vector<vector<Cell>> *grid): Ability{}, activePlayer{player}, grid{grid} {}

void Download::apply(int x, int y) {
    // link.getType() == "D" ? player->incrementDataCount() : player->incrementVirusCount();
    // (*grid)[link.getY()][link.getX()].setLinkNull();
    // (*grid)[link.getY()][link.getX()].notifyObservers();

    // get link of opponent player
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[x][y];
        Link *link = cell.getLink();
        link->setX(-1);
        link->setY(-1);
        link->getType() == 'D' ? activePlayer->incrementDataCount() : activePlayer->incrementVirusCount();
        cell.notifyObservers();
        cell.setLinkNull();
    } else {
        cout << "INVALID ABILITY MOVE" << endl;
    }
}

bool Download::checkValid(int x, int y) {
    Link *link = (*grid)[x][y].getLink();
    if (&link->getPlayer() == activePlayer) {
        return false;
    }
    
    return true;
}

char Download::getType() {
    return 'D';
}
