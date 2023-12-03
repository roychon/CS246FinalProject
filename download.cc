#include "download.h"

Download::Download(Type type, Player *player, vector<vector<Cell>> *grid): Ability(type), activePlayer{player}, grid{grid} {}

void Download::apply() {
    // link.getType() == "D" ? player->incrementDataCount() : player->incrementVirusCount();
    // (*grid)[link.getY()][link.getX()].setLinkNull();
    // (*grid)[link.getY()][link.getX()].notifyObservers();

    // get link of opponent player
    if (checkValid()) {
        Cell &cell = (*grid)[targetLink->getY()][targetLink->getX()];
        targetLink->setX(-1);
        targetLink->setY(-1);
        // activePlayer->incrementDownloads(targetLink->getType());
        cell.setLinkNull();
        cell.notifyObservers();
        isUsed = true;
    } else {
        cout << "INVALID ABILITY MOVE" << endl;
    }
}

// TODO: make sure they're downloading a valid link
bool Download::checkValid() {
    if (&targetLink->getPlayer() == activePlayer) {
        return false;
    }
    
    return true;
}

char Download::getType() {
    return 'D';
}

void Download::setTarget(Link *target) {
    targetLink = target;
}
