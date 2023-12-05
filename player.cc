#include "player.h"
#include <iostream>
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "scan.h"
#include "polarize.h"
#include "poweraugment.h"
#include "heal.h"
#include "takedown.h"
#include "conceal.h"
#include <map>
using namespace std;

Player::Player(const int playerID) : links(8), serverPorts(2), abilities(5), data{0}, viruses{0},
    numAbilitiesLeft{5}, playerID{playerID}, hasAbilityTurn{true}{
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

    return nullptr;
}

// ==========
// ABILITY LOGIC
void Player::useAbility(int id, int x, int y) {
    if (abilities[id - 1]->getIsUsed()) {
        throw(logic_error("Ability has been used already!\n"));
    } else {
        try {
            abilities[id - 1]->apply(x, y);
        } catch(logic_error &e) {
            cerr << e.what();
            return;
        }
        hasAbilityTurn = false;
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
            abilities[i] = make_unique<Polarize>(this, grid);
        }
        else if (abil == 'A') {
            abilities[i] = make_unique<PowerAugment>(this, grid);
        }
        else if (abil == 'H') {
            abilities[i] = make_unique<Heal>(this);
        }
        else if (abil == 'T') {
            abilities[i] = make_unique<Takedown>(this, grid);
        } 
        else if (abil == 'C') {
            abilities[i] = make_unique<Conceal>(this, grid);
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
        else if (abilities[i].get()->getType() == 'A') {
            cout << "Power Augment ";
        }
        else if (abilities[i].get()->getType() == 'H') {
            cout << "Heal ";
        }
        else if (abilities[i].get()->getType() == 'T') {
            cout << "Takedown ";
        }
        else if (abilities[i].get()->getType() == 'C') {
            cout << "Conceal ";
        }

        if (abilities[i].get()->getIsUsed() == 1) {
            cout << "- Used" << endl;
        }
        else {
            cout << "- Not Used" << endl;
        }
    }
}
int Player::getNumAbilitiesLeft() {
    return numAbilitiesLeft;
}

void Player::incrementDownloads(char type) {
    type == 'D' ? data++ : viruses++;
}

Ability* Player::getAbility(int ID) {
    return abilities[ID - 1].get();
}

void Player::decreaseVirusCount() {
    --viruses;
}

Link* Player::getLinkByID(char id) {
    for (auto &link : links) {
        if (link->getId() == id) {
            return link.get();
        }
    }
    return nullptr;
}

bool Player::getHasAbilityTurn() {
    return hasAbilityTurn;
}

void Player::reenableAbilityTurn() {
    hasAbilityTurn = true;
}
