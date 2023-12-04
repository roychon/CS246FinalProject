#ifndef __LINK_H__
#define __LINK_H__
#include <string>
#include "player.h"
using namespace std;

class Player;

// TODO: think about making Link abstract for lower coupling
// -> link will have to have a download function then
class Link {
    char id; // board display id, from a to z or A to Z depending on player
    int strength; // strength of link
    char type; // D: data, V : virus
    bool isRevealed;
    int x; // row
    int y; // col
    Player *player; // ptr to player who owns this link
    int moveFactor; // controls distance of movement for link on game board
    bool isDead;

public:
    Link();
    void move(int x, int y);
    int getMoveFactor();
    char getId();
    char getType();
    int getStrength();
    // void download(int n); // n: 'id' of the link
    Player &getPlayer(); // TODO: fix &
    int getX();
    int getY();
    bool getIsRevealed();
    bool getIsDead();
    void setIsDead();
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    void setType(char type);
    void setPlayer(Player *player);
    void revealLink();
    void setId(char id);
    void incrementMoveFactor(int factor);
    void augmentpower();
    void setRevealedFalse();

    // add any more fields as necessary
};

#endif
