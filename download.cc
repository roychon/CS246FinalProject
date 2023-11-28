#include "download.h"

Download::Download(Player *player, vector<vector<Cell>> *grid, int id): Ability{id}, player{player}, grid{grid} {}

void Download::apply(Link &link) {
    link.getType() == "D" ? player->changeDataCount() : player->changeVirusCount();
    (*grid)[link.getY()][link.getX()].setLinkNull();
    (*grid)[link.getY()][link.getX()].notifyObservers();
}
