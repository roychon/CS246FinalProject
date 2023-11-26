#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include "ability.h"
#include "link.h"

using namespace std;
class Player {
    vector<Link *> links; // player's links
    vector<Ability *> abilities; // player's abilities
    int data; // # data player downloads
    int viruses; // # viruses player downloads
    int numAbilitiesLeft; // # abilities player can use
    int playerID;

public:
    Player(vector<Link *> links, vector<Ability *> abilities);
    ~Player();
    void changeDataCount(); // increment data by 1
    void changeVirusCount(); // increment virus by 1
    void printPlayerDisplay(bool isActive);
    int getplayerID();
    bool HasLinkAt(int x, int y);
    // void updateScore();

    // add any more fields as necessary
};

#endif
