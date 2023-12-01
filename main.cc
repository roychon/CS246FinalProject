#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    string player1links = "Default";
    string player2links = "Default";
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
    }

    Game game;
    // can pass parameters into init, for command flags
    game.init(player1links, player2links);
    bool enhancementsOn = 0;

    string command;
    while (cin >> command) {
        if (command == "board") {
            game.display();
        }

        else if (command == "quit") {
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
                if (!game.move(linktomove, 0, 1)) {
                    cout << "Invalid Move";
                }
            }

            else if (direction == "right") {
                game.move(linktomove, 1, 0);
            }

            else if (direction == "left") {
                game.move(linktomove, -1, 0);
            }

            else if (direction == "down") {
                if (!game.move(linktomove, 0, -1)) {
                    cout << "Invalid Move";
                }
            }

            else {
                cout << "Incorrect input";
            }
            game.switchActivePlayer();
            game.display();
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
    }

    return 0;
}
