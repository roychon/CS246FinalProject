#ifndef __ABILITYMANAGER_H__
#define __ABILITYMANAGER_H__
#include <map>
#include <iostream>
#include <vector>
#include "ability.h"

#include "firewall.h"
#include "linkboost.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"

#include "link.h"
#include "player.h"
#include "cell.h"
using namespace std;

class AbilityManager {
    vector<unique_ptr<Ability>> abilities;
    Player *abilityOwner;
    vector<vector<Cell>> *grid;
    Type charToType(char initial);
    string typeToString(Type type);
    void constructAbility(Type type);
    public:
        explicit AbilityManager(string abilityString);
        void readArgs(int id);
};

#endif