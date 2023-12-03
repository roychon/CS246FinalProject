#include "abilitymanager.h"
using namespace std;

AbilityManager::AbilityManager(Player *abilityOwner, vector<vector<Cell>> *grid, string abilityString): 
    abilities(5), abilityOwner{abilityOwner}, grid{grid} {
        int i = 0;
    for (char c : abilityString) {
        Type type = charToType(c);
        if (type == Type::Download) {
            abilities[i] = make_unique<Download>(Type::Download, abilityOwner, grid);
        } else if (type == Type::Firewall) {
            abilities[i] = make_unique<Firewall>(Type::Firewall, abilityOwner, grid);
        } else if (type == Type::Polarize) {
            abilities[i] = make_unique<Polarize>(Type::Polarize, grid);
        } else if (type == Type::LinkBoost) {
            abilities[i] = make_unique<LinkBoost>(Type::LinkBoost, abilityOwner, grid);
        } else if (type == Type::Scan) {
            abilities[i] = make_unique<Scan>(Type::Scan, grid);
        }
        ++i;
        // constructAbility(abilityToMake);
    }
}

void AbilityManager::readArgs(int index) {
    // make setters, to set the fields of the resepctive abiltiies.
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

// remove this
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
    if (newAbility != nullptr) {
        abilities.emplace_back(move(newAbility)); 
        return;
    }
    cerr << "Failed" << endl;
}

void AbilityManager::displayAbilities() {
    // not working.. something seg faulting
    for (const auto &ability : abilities) {
        string abilityType = typeToString(ability->getAbilityType());
        cout << abilityType << endl;
        if (ability->getIsUsed()) {
            cout << "- Used" << endl;
        } else {
            cout << "- Not Used" << endl;
        }
    }
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

vector<Ability*> AbilityManager::getAbilities() {
    vector<Ability*> rawAbilities(abilities.size());
    for (size_t i = 0; i < abilities.size(); ++i) {
        rawAbilities[i] = abilities[i].get();
    }
    return rawAbilities;
}



