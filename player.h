#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include "ability.h"
#include "link.h"

class Link;

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
    bool hasLinkAt(int x, int y);
    void removeLinkAt(int x, int y);
    int getDataCount();
    int getVirusCount();
    // void updateScore();

    // add any more fields as necessary
};

#endif
