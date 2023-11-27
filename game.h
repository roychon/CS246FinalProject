#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include "board.h"
#include "player.h"
#include "link.h"

class Game {
    std::unique_ptr<Board> board;
    std::vector<std::unique_ptr<Player>> players;
    Player *activePlayer;
    Player *winningPlayer;

public:
    Game();
    bool checkWin();
    void display();
    bool move(Link *link, int x, int y);
//    void useAbility(int id); // id is 'id' of ability we want to use
    void init(); // initialize the Game

    // add any more fields as necessary
};

#endif
