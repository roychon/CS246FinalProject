#include <iostream>
#include <string>
#include <memory>
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    Game game;
    // can pass parameters into init, for command flags
    game.init();

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

            game.display();
            game.switchActivePlayer();
        }
    }

    return 0;
}
