#ifndef __LINK_H__
#define __LINK_H__
#include <string>
#include "player.h"
using namespace std;

class Player;

class Link {
    char id; // board display id, from a to z or A to Z depending on player
    int strength; // strength of link
    string type; // D: data, V : virus
    bool isRevealed;
    int x; // row
    int y; // col
    Player *player; // ptr to player who owns this link
    int moveFactor; // controls distance of movement for link on game board

public:
    void move(int x, int y);
    int getMoveFactor();
    char getId();
    string getType();
    int getStrength();
    // void download(int n); // n: 'id' of the link
    Player &getPlayer();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    void setType(string type);
    bool getIsRevealed();
    void RevealLink();

    // add any more fields as necessary
};

#endif
