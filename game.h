#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include "board.h"
#include "player.h"
#include "link.h"
using namespace std;

class Game {
    Board *board;
    vector<Player *> players;
    Player *activePlayer;
    Player *winningPlayer;

public:
    bool checkWin();
    void display();
    bool move(Link *link, int x, int y);
//    void useAbility(int id); // id is 'id' of ability we want to use
    void init(); // initialize the Game

    // add any more fields as necessary
};

#endif
