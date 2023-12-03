#include "player.h"
#include <iostream>
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "scan.h"
#include "polarize.h"
#include <map>
using namespace std;

// note, when init is fully setup likely have to pass abilities as a parameter
// temporarily passing "8" as # of links, if server port is coded as link, +2 so 10 links total.
Player::Player(const int playerID) : links(8), abilities{5}, data{0}, viruses{0}, numAbilitiesLeft{5}, playerID{playerID}{
    for (size_t i = 0; i < links.size(); ++i) {
        links[i] = make_unique<Link>();
    }
    // === DEFAULT CONSTRUCT SERVER PORTS ===
    for (size_t i = 0; i < 2; ++i) {
        serverports.emplace_back(make_unique<Link>());
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
    int y = (playerID == 1 ? 0 : 7);
    int x = 3;
    for (size_t i = 0; i < 2; ++i) {
        serverports[i]->setPlayer(this);
        serverports[i]->setId('S');
        serverports[i]->setX(x++);
        serverports[i]->setY(y);
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

bool Player::hasLinkAt(int x, int y) {
    for (auto &link : links) {
        if (x == link->getX() && y == link->getY()) {
            return true;
        }
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
    for (auto &link : links) {
        if (link->getX() == xCord && link->getY() == yCord) return link.get();
    }
    return nullptr; // will never get to this point
}

// ==========
// ABILITY CODE
void Player::useAbility(int id) {
    if (abilities[id]->getIsUsed()) {
        cout << "ABILITY IS USED" << endl;
    } else {
        playerID == 1 ? abilities[id]->apply(0, 7) : abilities[id]->apply(2, 0); // TODO: find the actual x, y coords, replace the 3, 3s
        numAbilitiesLeft--;
    }
}

void Player::setAbilities(string abilinit, vector<vector<Cell>> *grid) {
    for (int i = 0; i < 5; ++i) {
        char abil = abilinit[i];
        if (abil == 'L') {
            abilities[i] = make_unique<LinkBoost>(this, grid, i);
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

void Player::incrementDownloads(char type) {
    type == 'D' ? data++ : viruses++;
}

// ==== hasServerAt(xCord, yCord) ====
bool Player::hasServerAt(int xCord, int yCord) {
    for (auto &serverport : serverports) {
        if (serverport->getX() == xCord && serverport->getY() == yCord) return true;
    }
    return false;
}

// ==========
