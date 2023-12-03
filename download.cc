#include "download.h"

Download::Download(Player *player, vector<vector<Cell>> *grid): Ability{}, activePlayer{player}, grid{grid} {}

void Download::apply(int x, int y) {
    // link.getType() == "D" ? player->incrementDataCount() : player->incrementVirusCount();
    // (*grid)[link.getY()][link.getX()].setLinkNull();
    // (*grid)[link.getY()][link.getX()].notifyObservers();

    // get link of opponent player
    if (checkValid(x, y)) {
        Cell &cell = (*grid)[y][x];
        Link *link = cell.getLink();
        link->setX(-1);
        link->setY(-1);
        activePlayer->incrementDownloads(link->getType());
        cell.setLinkNull();
        cell.notifyObservers();
        isUsed = true;
    } else {
        cout << "INVALID ABILITY MOVE" << endl;
    }
}

// TODO: make sure they're downloading a valid link
bool Download::checkValid(int x, int y) {
    Link *link = (*grid)[y][x].getLink();
    if (&link->getPlayer() == activePlayer) {
        return false;
    }
    
    return true;
}

char Download::getType() {
    return 'D';
}
