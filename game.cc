#include "game.h"
using namespace std;

// also sets the other player to winning player
bool Game::checkWin() {
    for (auto player : players) {
        if (player->getDataCount() == 4) {
            winningPlayer = player;
            return true;
        }
        else if (player->getVirusCount() == 4) {
            if (player->getplayerID() == 1) {
                winningPlayer = players[1];
                return true;
            }
            else {
                winningPlayer = players[0];
                return true;
            }
        }
    }
    return false;
}

void Game::display() {
    Player *p1 = nullptr;
    Player *p2 = nullptr;

    for (auto player : players) {
        if (player->getplayerID() == 1) {
            p1 = player;
        }
        else {
            p2 = player;
        }
    }

    cout << "Player 1:" << endl;
    if (p1 == activePlayer) {
        p1->printPlayerDisplay(true);
    }
    else {
        p1->printPlayerDisplay(false);
    }

    board->printTextDisplay();

    cout << "Player 2:" << endl;
    if (p2 == activePlayer) {
        p2->printPlayerDisplay(true);
    }
    else {
        p2->printPlayerDisplay(false);
    }
}
