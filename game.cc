#include "game.h"
using namespace std;

Game::Game(): board{make_unique<Board>()}, players(2), 
    activePlayer{nullptr}, winningPlayer{nullptr}{
        for (int i = 0; i < 2; ++i) {
            players[i] = make_unique<Player>(i + 1);
        }
        // set active player to p1
        activePlayer = players[0].get();
        board->updateDisplayPOV(activePlayer);
}

void Game::init() {
    // call board setup, creating cells & displays
    board->setup();
    // create link shells and place them
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->initLinks();
        board->setupLinks(*(players[i]).get());
    }
    // right now, initializing empty, need to initialize from file or randomize
}

// also sets the other player to winning player
bool Game::checkWin() {
    for (auto &player : players) {
        if (player->getDataCount() == 4) {
            winningPlayer = player.get();
            return true;
        }
        else if (player->getVirusCount() == 4) {
            if (player->getPlayerID() == 1) {
                winningPlayer = players[1].get();
                return true;
            }
            else {
                winningPlayer = players[0].get();
                return true;
            }
        }
    }
    return false;
}

void Game::display() {
    Player *inactivePlayer = nullptr;
    for (auto &player : players) {
        if (player.get() != activePlayer) {
             inactivePlayer = player.get();
        }
    }
    inactivePlayer->printInactivePlayer();
    board->printTextDisplay();
    activePlayer->printActivePlayer();
    /*
    Player *p1 = nullptr;
    Player *p2 = nullptr;

    for (auto &player : players) {
        if (player->getPlayerID() == 1) {
            p1 = player.get();
        }
        else {
            p2 = player.get();
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
    */
}

// false (invalid move), true (valid move). Loop through 
bool Game::move(Link *link, int x, int y) {
    int xCord, yCord;

    // right: x = 1, left : x = -1, up : y = 1, down : y = -1
    // Player 1: top of the board
    if (activePlayer->getPlayerID() == 1) {
        xCord = link->getX() - x;
        yCord = link->getY() + y;
    } else {
    // Player 2: bottom of the board
        xCord = link->getX() + x;
        yCord = link->getY() - y;
    }

    if (board->isInvalidMove(*link, xCord, yCord, *activePlayer)) return false;

    // at this point, activePlayer's move is valid.
    // check if cell is occupied by opponent, find opponent(nonActivePlayer)
    Player *nonActivePlayer = (players[0]->getPlayerID() == activePlayer->getPlayerID()) ? players[1].get() : players[0].get();
    if (board->isOccupiedByOpponent(nonActivePlayer, xCord, yCord)) {
        // start battle
        board->battle(*activePlayer, *nonActivePlayer, *link, *(nonActivePlayer->findLinkAt(xCord, yCord)));
    } else {
        // activePlayer moves link to empty cell or server port
        board->move(activePlayer, nonActivePlayer, *link, xCord, yCord);
    }
    return true;
}

Player* Game::getActivePlayer() {
    return activePlayer;
}

void Game::switchActivePlayer() {
    if (activePlayer->getPlayerID() == 1) {
        for (auto &player : players) {
            if (player.get()->getPlayerID() == 2) {
                activePlayer = player.get();
            }
        }
    }
    else {
        for (auto &player : players) {
            if (player.get()->getPlayerID() == 1) {
                activePlayer = player.get();
            }
        }
    }
    board->updateDisplayPOV(activePlayer);
}
