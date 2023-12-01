#include "player.h"
#include <iostream>
#include <map>
using namespace std;

// note, when init is fully setup likely have to pass abilities as a parameter
// temporarily passing "8" as # of links, if server port is coded as link, +2 so 10 links total.
Player::Player(const int playerID) : links(8), data{0}, viruses{0}, numAbilitiesLeft{5}, playerID{playerID}{
    for (size_t i = 0; i < links.size(); ++i) {
        links[i] = make_unique<Link>();
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
}

void Player::incrementDataCount() {
    data++;
}

void Player::incrementVirusCount() {
    viruses++;
}

/*
void Player::printPlayerDisplay(bool isActive) {    
    cout << "Downloaded: " << data << "D, " << viruses << "V" << endl;
    cout << "Abilities: " << numAbilitiesLeft << endl;
    if (isActive) {
        char start = 'a';
        for (auto &link : links) {
            cout << start << ": " << link->getType() << link->getStrength();
            if (start == 'd' || start == 'h') cout << endl;
            else cout << " ";
            ++start;
        }
    }
    else {
        char start = 'A';
        for (auto &link : links) {
            cout << start << ": ";
            if (link->getIsRevealed()) {
                cout << link->getType() << link->getStrength();
            } else {
                cout << "?";
            }

            if (start == 'D' || start == 'H') cout << endl;
            else cout << " ";
            ++start;
        }
    }
}
*/

void Player::printActivePlayer() {
    cout << "Player " << playerID << ":" << endl;
    for (auto &link : links) {
        cout << link->getId() << ": ";
        cout << link->getType() << link->getStrength();
        if (link->getId() == 'D' || link->getId() == 'H' || link->getId() == 'd' || link->getId() == 'h') cout << endl;
        else cout << " ";
    }
}

void Player::printInactivePlayer() {
    cout << "Player " << playerID << ":" << endl;
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

int Player::getPlayerID() {
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
    if (abilities[0]->isUsed()) {
        cout << "ABILITY IS USED" << endl;
    } else {
        abilities[0]->apply(int x, int y); // apply ability
    }
}
// ==========
