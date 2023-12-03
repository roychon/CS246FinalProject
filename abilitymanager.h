#ifndef __ABILITYMANAGER_H__
#define __ABILITYMANAGER_H__
#include <map>
#include <iostream>
#include <vector>
#include <memory>
#include "ability.h"
#include "firewall.h"
#include "linkboost.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"

using namespace std;

class Player;
class Ability;
class Cell;
class Link;

class AbilityManager {
    vector<unique_ptr<Ability>> abilities;
    Player *abilityOwner;
    vector<vector<Cell>> *grid;
    Type charToType(char initial);
    string typeToString(Type type);
    void constructAbility(Type type);
    public:
        AbilityManager(Player *abilityOwner, vector<vector<Cell>> *grid, string abilityString);
        void readArgs(int index);
        void displayAbilities();
};

#endif