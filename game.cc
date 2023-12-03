#include "game.h"
using namespace std;

Game::Game(Xwindow &xw): board{make_unique<Board>(xw)}, players(2), 
    activePlayer{nullptr}, winningPlayer{nullptr}, enhancementsOn{false} {
        for (int i = 0; i < 2; ++i) {
            players[i] = make_unique<Player>(i + 1);
        }
        // set active player to p1
        activePlayer = players[0].get();
        board->updateDisplayPOV(activePlayer);
}

Game::Game(): board{make_unique<Board>()}, players(2), 
    activePlayer{nullptr}, winningPlayer{nullptr}, enhancementsOn{false} {
        for (int i = 0; i < 2; ++i) {
            players[i] = make_unique<Player>(i + 1);
        }
        // set active player to p1
        activePlayer = players[0].get();
        board->updateDisplayPOV(activePlayer);
}

void Game::init(string player1links, string player2links, string player1abilities, string player2abilities) {
    // call board setup, creating cells & displays
    board->setup();
    // create link shells and place them
    for (size_t i = 0; i < players.size(); ++i) {
        players[i]->initLinks();
        
        if (players[i].get()->getplayerID() == 1) {
        board->setupLinks(*(players[i]).get(), player1links);
        players[i].get()->setAbilities(player1abilities, board.get()->getGrid());
        }
        else {
        board->setupLinks(*(players[i]).get(), player2links);    
        players[i].get()->setAbilities(player2abilities, board.get()->getGrid());
        }
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
            if (player->getplayerID() == 1) {
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

void Game::display(bool graphicsOn) {
    Player *inactivePlayer = nullptr;
    for (auto &player : players) {
        if (player.get() != activePlayer) {
             inactivePlayer = player.get();
        }
    }
    
    board->getGD()->playerDisplays(activePlayer, inactivePlayer);

    if (enhancementsOn == true) {
        inactivePlayer->printInactivePlayer();
        board->printTextDisplay();
        activePlayer->printActivePlayer();
    }
    else {
    if (activePlayer->getplayerID() == 1) {
        activePlayer->printActivePlayer();
    }
    else {
        inactivePlayer->printInactivePlayer();
    }
    board->printTextDisplay();
    if (activePlayer->getplayerID() == 2) {
        activePlayer->printActivePlayer();
    }
    else {
        inactivePlayer->printInactivePlayer();
    }
    }
}

// false (invalid move), true (valid move). Loop through 
bool Game::move(Link *link, int x, int y) {
    int moveFactor = link->getMoveFactor();
    int xCord, yCord;
    int newX = x * moveFactor;
    int newY = y * moveFactor;

    // right: x = 1, left : x = -1, up : y = 1, down : y = -1
    // Player 1: top of the board
    if (activePlayer->getplayerID() == 1) {
        xCord = link->getX() - newX;
        yCord = link->getY() + newY;
    } else {
    // Player 2: bottom of the board
        xCord = link->getX() + newX;
        yCord = link->getY() - newY;
    }
    
    if (board->isInvalidMove(*link, xCord, yCord, *activePlayer)) return false;


    // at this point, activePlayer's move is valid.
    // check if cell is occupied by opponent, find opponent(nonActivePlayer)

    Player *nonActivePlayer = (players[0]->getplayerID() == activePlayer->getplayerID()) ? players[1].get() : players[0].get();
    if (board->isOccupiedByOpponent(nonActivePlayer, xCord, yCord)) { // check if you can instantiate a battle
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
    if (activePlayer->getplayerID() == 1) {
        for (auto &player : players) {
            if (player.get()->getplayerID() == 2) {
                activePlayer = player.get();
            }
        }
    }
    else {
        for (auto &player : players) {
            if (player.get()->getplayerID() == 1) {
                activePlayer = player.get();
            }
        }
    }
    board->updateDisplayPOV(activePlayer);
}


// =========
// CODE FOR ABILITIES

void Game::activePlayerUseAbility(int id) {
    // lookup
    activePlayer->useAbility(id);
}
// =========

void Game::toggleenhancementsOn() {
    if (enhancementsOn == true) {
        enhancementsOn = false;
        board.get()->toggleenhancementsOn();
    }
    else {
        enhancementsOn = true;
        board.get()->toggleenhancementsOn();
    }
}

Player* Game::getWinningPlayer() {
    return winningPlayer;
}
