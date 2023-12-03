#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include <memory>
#include "ability.h"
#include "link.h"

class Link;
class Ability;
class Cell;

using namespace std;
class Player {
    vector<unique_ptr<Link>> links; // player's links
    // unique_ptr<AbilityManager> manager;
    // === added: server ports ===
    vector<unique_ptr<Link>> serverPorts;
    vector<unique_ptr<Ability>> abilities; // player's abilities
    int data; // # data player downloads
    int viruses; // # viruses player downloads
    int numAbilitiesLeft; // # abilities player can use
    const int playerID;
    char linkIDLookUp(const int playerID, const int index);

public:
    Player(const int playerID);
    // ~Player();
    void initLinks(); // Sets player pointers and characer IDs of each link.
    // TODO: create these into one function
    // void incrementDataCount(); // increment data by 1
    // void incrementVirusCount(); // increment virus by 1
    void incrementDownloads(char type);
    void printPlayerDisplay(bool isActive);
    void printActivePlayer();
    void printInactivePlayer();
    int getplayerID();
    vector<Link*> getLinks();
    vector<Link*> getServerPorts();
    bool hasLinkAt(int x, int y);
    void removeLinkAt(int x, int y);
    int getDataCount();
    int getVirusCount();
    Link *findLinkAt(int xCord, int yCord);
    // void updateScore();
    void useAbility(int id, int x, int y);
    void setAbilities(string abilinit, vector<vector<Cell>> *grid);
    void printAbilities();
    int getnumAbilitiesLeft();
    Ability *getAbility(int ID);
    // bool hasServerAt(int xCord, int yCord); merged with has hasLInkAt
    // add any more fields as necessary
};

#endif
