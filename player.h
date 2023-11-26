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

public:
    Player();
    ~Player();

    void activeDisplay();
    void nonActiveDisplay();
    void updateScore();

    // add any more fields as necessary
};

#endif
