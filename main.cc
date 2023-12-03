#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    string player1links = "Default";
    string player2links = "Default";
    string player1abilities = "LFDSP";
    string player2abilities = "LFDSP";
    bool graphicsOn = false;
    // Command line arguments
    for (int i = 1; i < argc; ++i) {
        string cmd = argv[i];
        if (cmd == "-link1") {
            ++i;
            ifstream linkfile{argv[i]};
            string total;
            string word;
            while (linkfile >> word) {
                total = total + word;
            }
            player1links = total;
        }

        else if (cmd == "-link2") {
            ++i;
            ifstream linkfile{argv[i]};
            string total;
            string word;
            while (linkfile >> word) {
                total = total + word;
            }
            player2links = total;
        }

        else if (cmd == "-ability1") {
            ++i;
            player1abilities = argv[i];
        }

        else if (cmd == "-ability2") {
            ++i;
            player2abilities = argv[i];
        }

        else if (cmd == "-graphics") {
            graphicsOn = true;
        }
    }

    Game game;
    Xwindow *xw = nullptr;
    if (graphicsOn) {
    xw = new Xwindow;
    game = Game{*xw};
    }
    // can pass parameters into init, for command flags
    game.init(player1links, player2links, player1abilities, player2abilities);
    bool enhancementsOn = 0;
    
    string command;
    while (cin >> command) {
        if (command == "board") {
            game.display(graphicsOn);
        }

        else if (command == "quit") {
            delete xw;
            break;
        }

        else if (command == "move") {
            char whichlink;
            string direction;
            cin >> whichlink >> direction;
            Link *linktomove;

            for (auto link : game.getActivePlayer()->getLinks()) {
                if (link->getId() == whichlink) {
                    linktomove = link;
                }
            }
            
            if (direction == "up") {
                game.move(linktomove, 0, 1);
            }

            else if (direction == "right") {
                game.move(linktomove, 1, 0);
            }

            else if (direction == "left") {
                game.move(linktomove, -1, 0);
            }

            else if (direction == "down") {
                game.move(linktomove, 0, -1);
            }
            
            else {
                cout << "Incorrect input";
            }
            game.switchActivePlayer();
            game.display(graphicsOn);
            if (game.checkWin() == true) {
                cout << "Player " << game.getWinningPlayer()->getplayerID() << " Wins!" << endl;
                delete xw;
                break;
            }
        }

        else if (command == "enhancements") {
            if (enhancementsOn == true) {
                enhancementsOn = false;
                game.toggleenhancementsOn();
            }
            else {
                enhancementsOn = true;
                game.toggleenhancementsOn();
            }
        }

        else if (command == "abilities") {
            game.getActivePlayer()->printAbilities();
        }
        else if (command == "ability") {
            int id;
            cin >> id;
            char whichlink;
            int x;
            int y;
            if (game.getActivePlayer()->getAbility(id)->getType() == 'L') {
                cin >> whichlink;
                for (auto link : game.getActivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                game.getActivePlayer()->useAbility(id, x, y);
            }
            else if (game.getActivePlayer()->getAbility(id)->getType() == 'D') {
                cin >> whichlink;
                for (auto link : game.getActivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                game.getActivePlayer()->useAbility(id, x, y);
            }
            else if (game.getActivePlayer()->getAbility(id)->getType() == 'F') {
                cin >> x >> y;
                game.getActivePlayer()->useAbility(id, x, y);
            }
            else if (game.getActivePlayer()->getAbility(id)->getType() == 'P') {
                cin >> whichlink;
                for (auto link : game.getActivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                for (auto link : game.getInactivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                game.getActivePlayer()->useAbility(id, x, y);
            }
            else if (game.getActivePlayer()->getAbility(id)->getType() == 'S') {
                cin >> whichlink;
                for (auto link : game.getActivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                for (auto link : game.getInactivePlayer()->getLinks()) {
                    if (link->getId() == whichlink) {
                        x = link->getX();
                        y = link->getY();
                    }
                }
                game.getActivePlayer()->useAbility(id, x, y);
            }
            game.display(graphicsOn);
        }
    }
    
    return 0;
}
