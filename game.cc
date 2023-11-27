#include "game.h"
using namespace std;

Game::Game(): board{board = make_unique<Board>()}, players(2), 
    activePlayer{nullptr}, winningPlayer{nullptr}{
        for (int i = 0; i < 2; ++i) {
            players[i] = make_unique<Player>();
        }
    }

void Game::init() {
    // call board setup, creating cells & displays
    board.setup();
    // create link shells and place them
    
}

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

// false (invalid move), true (valid move). Loop through 
bool Game::move(Link *link, int x, int y) {
    int xCord, yCord;

    // right: x = 1, left : x = -1, up : y = 1, down : y = -1
    // Player 1: top of the board
    if (activePlayer->getplayerID() == 1) {
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
    Player *nonActivePlayer = (players[0]->getplayerID() == activePlayer->getplayerID()) ? players[1] : players[0];
    if (board->isOccupiedByOpponent(nonActivePlayer, xCord, yCord)) {
        // start battle
        board->battle(*activePlayer, *nonActivePlayer, *link, *(nonActivePlayer->findLinkAt(xCord, yCord)));
    } else {
        // activePlayer moves link to empty cell or server port
        board->move(activePlayer, nonActivePlayer, *link, x, y);
    }
    return true;
}
