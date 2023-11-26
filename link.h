#ifndef __LINK_H__
#define __LINK_H__
#include <string>
#include "player.h"
using namespace std;

class Link {
    int strength; // strength of link
    string type; // type of link
    bool isRevealed;
    int row;
    int col;
    Player *player; // ptr to player who owns this link
    int moveFactor; // controls distance of movement for link on game board


public:
    void move(int x, int y);
    string getType();
    int getStrength();
    void download(int n); // n: 'id' of the link
    Player &getPlayer();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    void setType(string type);

    // add any more fields as necessary
};

#endif
