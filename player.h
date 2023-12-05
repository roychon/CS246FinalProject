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
    vector<unique_ptr<Link>> serverPorts;
    vector<unique_ptr<Ability>> abilities; // player's abilities
    int data; // # data player downloads
    int viruses; // # viruses player downloads
    int numAbilitiesLeft; // # abilities player can use
    const int playerID;
    char linkIDLookUp(const int playerID, const int index);
    bool hasAbilityTurn;

public:
    Player(const int playerID);
    void initLinks(); // Sets player pointers and characer IDs of each link.
    void incrementDownloads(char type); // Increments a player's downloads
    void printActivePlayer(); // Print's the active player's stats
    void printInactivePlayer(); // Print's the inactive player's stats
    int getplayerID();
    vector<Link*> getLinks();
    vector<Link*> getServerPorts();
    bool hasLinkAt(int x, int y); // Checks if the player has a link at a location
    void removeLinkAt(int x, int y); // Removes a link at a given location
    int getDataCount();
    int getVirusCount();
    bool getHasAbilityTurn();
    Link *findLinkAt(int xCord, int yCord); // Returns a pointer to a link at a location
    void useAbility(int id, int x, int y); // Applies an ability with the given id and coords
    void setAbilities(string abilinit, vector<vector<Cell>> *grid); // Sets the abilities of a player
    void reenableAbilityTurn();
    void printAbilities(); // Prints the abilities
    int getNumAbilitiesLeft();
    Ability *getAbility(int ID);
    void decreaseVirusCount();
    Link *getLinkByID(char id);
};

#endif
