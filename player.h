#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <memory>
#include "ability.h"
#include "link.h"

class Link;

using namespace std;
// TODO: make player class abstract and have player1, player2 class inherit to lower coupling
class Player {
    vector<unique_ptr<Link>> links; // player's links
    vector<unique_ptr<Ability>> abilities; // player's abilities
    int data; // # data player downloads
    int viruses; // # viruses player downloads
    int numAbilitiesLeft; // # abilities player can use
    const int playerID;
    char linkIDLookUp(const int playerID, const int index);

public:
    Player(const int playerID);
    ~Player();
    void initLinks(); // Sets player pointers and characer IDs of each link.
    void changeDataCount(); // increment data by 1
    void changeVirusCount(); // increment virus by 1
    void printPlayerDisplay(bool isActive);
    int getplayerID();
    vector<Link*> getLinks();
    bool hasLinkAt(int x, int y);
    void removeLinkAt(int x, int y);
    int getDataCount();
    int getVirusCount();
    Link *findLinkAt(int xCord, int yCord);
    // void updateScore();

    // add any more fields as necessary
};

#endif
