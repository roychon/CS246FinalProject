#ifndef __CLParse_H__
#define __CLParse_H__
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdexcept>
using namespace std;

class CLParse {
    bool hasInvalidDeck(string &myString);
public:
    void parseLinks(string &playerlinks, string filename);
    void parseAbilities(string &abilities, string input, int playerNum);
};
#endif
