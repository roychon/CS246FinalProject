#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
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
    Game(Xwindow &xw);
    Game();
    bool checkWin();
    void display(bool graphicsOn);
    void move(Link *link, int x, int y);
    void init(string player1links, string player2links, string player1abilities, string player2abilities); // initialize the Game
    Player* getActivePlayer();
    void switchActivePlayer();
    void toggleEnhancementsOn();
    Player* getWinningPlayer();
    Player* getInactivePlayer();
    void runSequence(string filename, bool graphicsOn);
};

#endif
