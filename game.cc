#include "game.h"
using namespace std;

Game::Game(Xwindow *xw): board{make_unique<Board>(xw)}, players(2), 
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
    
    if (graphicsOn) {
        board->getGD()->playerDisplays(activePlayer, inactivePlayer);
    }

    cout << endl;
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
    cout << endl;
}

void Game::move(Link *link, int x, int y) {
    int moveFactor = link->getMoveFactor();
    if (moveFactor == 0) {
        cout << "Should've remembered this can't be moved...";
        return;
    }
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
    
    if (board->isInvalidMove(*link, xCord, yCord, *activePlayer)) throw(logic_error("Invalid move.\n"));


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
    activePlayer->reenableAbilityTurn();
}

void Game::toggleEnhancementsOn() {
    enhancementsOn = !enhancementsOn;
    board.get()->toggleEnhancementsOn();
}

Player* Game::getWinningPlayer() {
    return winningPlayer;
}

Player* Game::getInactivePlayer() {
    for (auto &player : players) {
        if (player.get() != activePlayer) {
            return player.get();
        }
    }
    return nullptr; // should never be reached if used properly
}

void Game::runSequence(string filename, bool graphicsOn) {
    ifstream sequencefile{filename};
    string cmdexecute;
    while (getline(sequencefile, cmdexecute)) {
        istringstream cmdparse{cmdexecute};
        string individualcmd;
        cmdparse >> individualcmd;
        if (individualcmd == "board") {
            display(graphicsOn);
        }

        else if (individualcmd == "quit") {
            return;
        }

        else if (individualcmd == "move") {
            char whichLink;
            string direction;
            cmdparse >> whichLink >> direction;
            Link *linkToMove = getActivePlayer()->getLinkByID(whichLink);
            if (linkToMove == nullptr) {
                cout << "This is not one of your links!" << endl;
                continue;
            } else if (linkToMove->getIsDead()) {
                cout << "This link no longer exists." << endl;
                continue;
            }
            try {
                int x = 0;
                int y = 0;
                if (direction == "up") y = 1;
                else if (direction == "right") x = 1;
                else if (direction == "left") x = -1;
                else if (direction == "down") y = -1;
                else {
                    cout << "Invalid direction." << endl;
                    continue;
                }
    
                move(linkToMove, x, y);
                
            } catch(logic_error &e) {
                cerr << e.what();
                continue;
            }
            switchActivePlayer();
            display(graphicsOn);
            if (checkWin() == true) {
                cout << "Player " << getWinningPlayer()->getplayerID() << " Wins!" << endl;
                break;
            }
        }

        else if (individualcmd == "enhancements") {
            enhancementsOn = !enhancementsOn;
            toggleEnhancementsOn();
        }

        else if (individualcmd == "abilities") {
            getActivePlayer()->printAbilities();
        }
        else if (individualcmd == "ability") {
            int id, x, y;
            cmdparse >> id;
            char whichLink;
            char abilityType = getActivePlayer()->getAbility(id)->getType();

            if (!getActivePlayer()->getHasAbilityTurn()) {
                cout << "You've already used an ability this turn!" << endl;
                continue;
            }

            if (getActivePlayer()->getNumAbilitiesLeft() == 0) {
                cout << "You're out of abilities!" << endl;
                continue;
            }
            try {
                // target is only active player's link
                if (abilityType == 'L' || abilityType == 'A') {
                    cmdparse >> whichLink;
                    Link *targetLink = getActivePlayer()->getLinkByID(whichLink);
                    if (targetLink == nullptr) {
                        cout << "This is not one of your links!" << endl;
                        continue;
                    } else if (targetLink->getIsDead()) {
                        cout << "This link no longer exists." << endl;
                        continue;
                    }
                    x = targetLink->getX();
                    y = targetLink->getY();
                    getActivePlayer()->useAbility(id, x, y);
                }
                // target is only inactive player's link
                else if (abilityType == 'D' || abilityType == 'T') {
                    cmdparse >> whichLink;
                    Link *targetLink = getInactivePlayer()->getLinkByID(whichLink);
                    if (targetLink == nullptr) {
                        cout << "This is not one of your opponent's links!" << endl;
                        continue;
                    } else if (targetLink->getIsDead()) {
                        cout << "This link no longer exists." << endl;
                        continue;
                    }
                    x = targetLink->getX();
                    y = targetLink->getY();
                    getActivePlayer()->useAbility(id, x, y);
                }
                // target is either active or inactive player's link
                else if (abilityType == 'P' || abilityType == 'S') {
                    cmdparse >> whichLink;
                    Link *targetLink = getActivePlayer()->getLinkByID(whichLink);
                    // not your own links, so check if it's opponent's
                    if (targetLink == nullptr) {
                        targetLink = getInactivePlayer()->getLinkByID(whichLink);
                    }
                    if (targetLink == nullptr) {
                        cout << "This is not neither one of your own or your opponent's links!" << endl;
                        continue;
                    } else if (targetLink->getIsDead()) {
                        cout << "This link no longer exists." << endl;
                        continue;
                    }
                    if (abilityType == 'S' && targetLink->getIsRevealed()) {
                        cout << "This link is already revealed... cannot be scanned." << endl;
                        continue;
                    }

                    x = targetLink->getX();
                    y = targetLink->getY();
                    getActivePlayer()->useAbility(id, x, y);
                }
                // target is coord
                else if (abilityType == 'F') {
                    cmdparse >> x >> y;
                    getActivePlayer()->useAbility(id, x, y);
                }
                // target is not a coord or link
                else if (abilityType == 'H' || abilityType == 'C') {
                    getActivePlayer()->useAbility(id, -1, -1);
                }
            } catch(logic_error &e) {
                cerr << e.what();
                continue;
            }
            display(graphicsOn);
            cout << "Ability " << id << " used!" << endl;
            if (checkWin() == true) {
                cout << "Player " << getWinningPlayer()->getplayerID() << " Wins!" << endl;
                break;
            }
        }
        else if (individualcmd == "sequence") {
            string filename;
            cmdparse >> filename;
            runSequence(filename, graphicsOn);
        }
    }
}

