#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include <memory>
#include "board.h"
#include "player.h"
#include "link.h"
using namespace std;

class Game {
    unique_ptr<Board> board;
    vector<unique_ptr<Player>> players;
    Player *activePlayer;
    Player *winningPlayer;
    bool enhancementsOn;

public:
    Game();
    bool checkWin();
    void display();
    bool move(Link *link, int x, int y);
//    void useAbility(int id); // id is 'id' of ability we want to use
    void init(string player1links, string player2links); // initialize the Game
    Player* getActivePlayer();
    void switchActivePlayer();
    void activePlayerUseAbility(int id); // call activePlayer's useAbility function
    void toggleenhancementsOn();

    // add any more fields as necessary
};

#endif
