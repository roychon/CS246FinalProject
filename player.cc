#include "player.h"
#include <iostream>
using namespace std;
Player::Player(vector<Link *> links, vector<Ability *> abilities) : links{links}, abilities{abilities}, data{0}, viruses{0}, numAbilitiesLeft{5} {}

void Player::changeDataCount() {
    data++;
}

void Player::changeVirusCount() {
    viruses++;
}

void Player::printPlayerDisplay(bool isActive) {    
    cout << "Downloaded: " << data << "D, " << viruses << "V" << endl;
    cout << "Abilities: " << numAbilitiesLeft << endl;
    if (isActive) {
        char start = 'a';
        for (auto link : links) {
            cout << start << ": " << link->getType() << link->getStrength();
            if (start == 'd' || start == 'h') cout << endl;
            else cout << " ";
            ++start;
        }
    }
    else {
        char start = 'A';
        for (auto link : links) {
            cout << start << ": ";
            if (link->getIsRevealed()) {
                cout << link->getType() << link->getStrength();
            } else {
                cout << "?";
            }

            if (start == 'D' || start == 'H') cout << endl;
            else cout << " ";
        }
    }
}
