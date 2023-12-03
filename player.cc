#include "player.h"
using namespace std;

// note, when init is fully setup likely have to pass abilities as a parameter
// temporarily passing "8" as # of links, if server port is coded as link, +2 so 10 links total.
Player::Player(const int playerID) : links(8), serverPorts(2), data{0}, viruses{0}, numAbilitiesLeft{5}, playerID{playerID}{
    for (size_t i = 0; i < links.size(); ++i) {
        links[i] = make_unique<Link>();
    }
    // === DEFAULT CONSTRUCT SERVER PORTS ===
    for (size_t i = 0; i < serverPorts.size(); ++i) {
        serverPorts[i] = make_unique<Link>();
    }
}

// Assigns the player's link a character ID for their display on the board.
char Player::linkIDLookUp(const int playerID, const int index) {
    std::map<int, char> linkIDMap;
    char baseChar = 'a';
    if (playerID == 2) baseChar -= 32;
    for (int i = 0; i < 8; ++i) {
        linkIDMap[i] = baseChar + i;
    }
    return linkIDMap[index];
}

void Player::initLinks() {
    for (size_t i = 0; i < links.size(); ++i) {
        links[i]->setPlayer(this);
        links[i]->setId(linkIDLookUp(playerID, i));

    }

    // === SERVER PORTS ===
    for (size_t i = 0; i < serverPorts.size(); ++i) {
        serverPorts[i]->setPlayer(this);
        serverPorts[i]->setId('S');
        serverPorts[i]->setType('S');
    }
}

// void Player::incrementDataCount() {
//     data++;
// }

// void Player::incrementVirusCount() {
//     viruses++;
// }

// void Player::printPlayerDisplay(bool isActive) {    
//     cout << "Downloaded: " << data << "D, " << viruses << "V" << endl;
//     cout << "Abilities: " << numAbilitiesLeft << endl;
//     if (isActive) {
//         char start = 'a';
//         for (auto &link : links) {
//             cout << start << ": " << link->getType() << link->getStrength();
//             if (start == 'd' || start == 'h') cout << endl;
//             else cout << " ";
//             ++start;
//         }
//     }
//     else {
//         char start = 'A';
//         for (auto &link : links) {
//             cout << start << ": ";
//             if (link->getIsRevealed()) {
//                 cout << link->getType() << link->getStrength();
//             } else {
//                 cout << "?";
//             }

//             if (start == 'D' || start == 'H') cout << endl;
//             else cout << " ";
//             ++start;
//         }
//     }
// }

void Player::printActivePlayer() {
    cout << "Player " << playerID << ":" << endl;
    cout << "Downloaded: " << data << "D, " << viruses << "V" << endl;
    cout << "Abilities: " << numAbilitiesLeft << endl;
    for (auto &link : links) {
        cout << link->getId() << ": ";
        cout << link->getType() << link->getStrength();
        if (link->getId() == 'D' || link->getId() == 'H' || link->getId() == 'd' || link->getId() == 'h') cout << endl;
        else cout << " ";
    }
}

void Player::printInactivePlayer() {
    cout << "Player " << playerID << ":" << endl;
    cout << "Downloaded: " << data << "D, " << viruses << "V" << endl;
    cout << "Abilities: " << numAbilitiesLeft << endl;
    for (auto &link : links) {
        cout << link->getId() << ": ";
        if (link->getIsRevealed()) {
            cout << link->getType() << link->getStrength();
        } else {
            cout << "?";
        }

        if (link->getId() == 'D' || link->getId() == 'H' || link->getId() == 'd' || link->getId() == 'h') cout << endl;
        else cout << " ";
    }
}

int Player::getplayerID() {
    return playerID;
}

vector<Link*> Player::getLinks() {
    vector<Link*> rawLinks(links.size());
    for (size_t i = 0; i < links.size(); ++i) {
        rawLinks[i] = links[i].get();
    }
    return rawLinks;
}

vector<Link*> Player::getServerPorts() {
    vector<Link*> rawLinks(serverPorts.size());
    for (size_t i = 0; i < serverPorts.size(); ++i) {
        rawLinks[i] = serverPorts[i].get();
    }
    return rawLinks;
}

bool Player::hasLinkAt(int x, int y) {
    for (auto &link : links) {
        if (x == link->getX() && y == link->getY()) return true;
    }

    for (auto &serverPort : serverPorts) {
        if (x == serverPort->getX() && y == serverPort->getY()) return true;
    }
    return false;
}

int Player::getDataCount() {
    return data;
}

int Player::getVirusCount() {
    return viruses;
}

Link *Player::findLinkAt(int xCord, int yCord) {
    // search links
    for (auto &link : links) {
        if (link->getX() == xCord && link->getY() == yCord) return link.get();
    }

    // search server ports
    for (auto &server : serverPorts) {
        if (server->getX() == xCord && server->getY() == yCord) return server.get();
    }

    return nullptr; // should never reach this point
}

// ======= MODIFIED ABILITY MANAGER FUNCTIONS ========

void Player::useAbility(int id) {
    abilityDeck->readArgs(id - 1);
}

void Player::setAbilities(string abilinit, vector<vector<Cell>> *grid) {
    abilityDeck = make_unique<AbilityManager>(this, grid, abilinit);
}

// broken, seg faulting.
void Player::printAbilities() {
    abilityDeck->displayAbilities();
}

// ==========
// ABILITY CODE

/*

void Player::useAbility(int id) {
    if (abilities[id]->getIsUsed()) {
        cout << "ABILITY IS USED" << endl;
    } else {
        playerID == 1 ? abilities[id]->apply(0, 0) : abilities[id]->apply(0, 7); // TODO: find the actual x, y coords, replace the 3, 3s
        numAbilitiesLeft--;
    }
}

void Player::setAbilities(string abilinit, vector<vector<Cell>> *grid) {
    for (int i = 0; i < 5; ++i) {
        char abil = abilinit[i];
        if (abil == 'L') {
            abilities[i] = make_unique<LinkBoost>(this, grid);
        }
        else if (abil == 'F') {
            abilities[i] = make_unique<Firewall>(this, grid);
        }
        else if (abil == 'D') {
            abilities[i] = make_unique<Download>(this, grid);
        }
        else if (abil == 'S') {
            abilities[i] = make_unique<Scan>(grid);
        }
        else if (abil == 'P') {
            abilities[i] = make_unique<Polarize>(grid);
        }
    }
}

void Player::printAbilities() {
    for (int i = 0; i < 5; ++i) {
        cout << "ID " << i + 1 << ": ";
        if (abilities[i].get()->getType() == 'L') {
            cout << "Link boost ";
        }
        else if (abilities[i].get()->getType() == 'D') {
            cout << "Download ";
        }
        else if (abilities[i].get()->getType() == 'P') {
            cout << "Polarize ";
        }
        else if (abilities[i].get()->getType() == 'F') {
            cout << "Firewall ";
        }
        else if (abilities[i].get()->getType() == 'S') {
            cout << "Scan ";
        }

        if (abilities[i].get()->getIsUsed() == 1) {
            cout << "- Used" << endl;
        }
        else {
            cout << "- Not Used" << endl;
        }
    }
}

*/

void Player::incrementDownloads(char type) {
    type == 'D' ? data++ : viruses++;
}

// ==== hasServerAt(xCord, yCord) ====
/*
bool Player::hasServerAt(int xCord, int yCord) {
    for (auto &serverport : serverPorts) {
        if (serverport->getX() == xCord && serverport->getY() == yCord) return true;
    }
    return false;
}
*/

// ==========
