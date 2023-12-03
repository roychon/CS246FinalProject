#include "abilitymanager.h"
using namespace std;

AbilityManager::AbilityManager(Player *abilityOwner, vector<vector<Cell>> *grid, string abilityString): 
    abilities(5), abilityOwner{abilityOwner}, grid{grid} {
    for (char c : abilityString) {
        Type abilityToMake = charToType(c);
        constructAbility(abilityToMake);
    }
}

void AbilityManager::readArgs(int index) {
    /*
    Type type = abilities[id]->getAbilityType();
    char linkInput;
    int xInput, yInput, x, y;
    bool isLinkCommand = false;
    if (type == Type::Firewall) {
        cin << x << y;
    } else if (type == Type::Download) {
        cin << linkInput;
        isLinkCommand = true;
    } else if (type == Type::Polarize) {
        cin << linkInput;
        isLinkCommand = true;
    } else if (type == Type::LinkBoost) {
        cin << linkInput;
        isLinkCommand = true;
    } else if (type == Type::Scan) {
        cin << linkInput;
        isLinkCommand = true;
    }

    // toDO, actually find the link coords here
    if (isLinkCommand) {
        x = -1;
        y = -1;
    }
    abilities[id]->apply(x, y);
    */
}

void AbilityManager::constructAbility(Type type) {
    unique_ptr<Ability> newAbility;
    if (type == Type::Download) {
        newAbility = make_unique<Download>(Type::Download, abilityOwner, grid);
    } else if (type == Type::Firewall) {
        newAbility = make_unique<Firewall>(Type::Firewall, abilityOwner, grid);
    } else if (type == Type::Polarize) {
        newAbility = make_unique<Polarize>(Type::Polarize, grid);
    } else if (type == Type::LinkBoost) {
        newAbility = make_unique<LinkBoost>(Type::LinkBoost, abilityOwner, grid);
    } else if (type == Type::Scan) {
        newAbility = make_unique<Scan>(Type::Scan, grid);
    }
    if (newAbility != nullptr) abilities.emplace_back(move(newAbility));
    cerr << "Failed" << endl;
}

Type AbilityManager::charToType(char initial) {
    std::map<char, Type> charTypeMap;
    charTypeMap['D'] = Type::Download;
    charTypeMap['F'] = Type::Firewall;
    charTypeMap['P'] = Type::Polarize;
    charTypeMap['L'] = Type::LinkBoost;
    charTypeMap['S'] = Type::Scan;
    return charTypeMap[initial];
}

string AbilityManager::typeToString(Type type) {
    std::map<Type, string> typeStringMap;
    typeStringMap[Type::Download] = "Download";
    typeStringMap[Type::Firewall] = "Firewall";
    typeStringMap[Type::Polarize] = "Polarize";
    typeStringMap[Type::LinkBoost] = "LinkBoost";
    typeStringMap[Type::Scan] = "Scan";
    return typeStringMap[type];
}



