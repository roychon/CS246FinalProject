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
    int activeID = activePlayer->getplayerID();
    
    int nonActiveID = -1;
    for (auto player : players) {
        if (player != activePlayer) {
            nonActiveID = player->getplayerID();
        }
    }

    cout << "Player " << activeID << ":" << endl;
    activePlayer->printPlayerDisplay(true);
    board->printTextDisplay();
    cout << "Player " << nonActiveID << ":" << endl;
    players[nonActiveID]->printPlayerDisplay(false);
}
