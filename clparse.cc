#include "clparse.h"
using namespace std;

bool CLParse::hasInvalidDeck(string &myString) {
    map<char, int> letterCount;
    string possibleAbilities = "LFDSPAHCT"; // All possible ability codes
    for (char letter : myString) {
        if (!(possibleAbilities.find(letter) != string::npos)) return true;
        letterCount[letter]++;
        if (letterCount[letter] > 2) return true;
    }
    return false;
}

void CLParse::parseLinks(string &playerlinks, string filename) {
    string total;
    string word;
    ifstream linkfile{filename};
    while (linkfile >> word) {
        total = total + word;
    }
    playerlinks = total;
}

void CLParse::parseAbilities(string &abilities, string input, int playerNum) {
    if (hasInvalidDeck(input) || input.length() != 5) {
        throw(logic_error("Invalid ability selection for player " + to_string(playerNum) + ". Setting default abilities.\n"));
    }
    abilities = input;
}