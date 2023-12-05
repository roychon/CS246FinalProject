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
    Game(Xwindow *xw);
    Game();
    bool checkWin(); // Checks if a player has won
    void display(bool graphicsOn); // Displays the board and player stats
    void move(Link *link, int x, int y); // Applies a move given a link and direction
    void init(string player1links, string player2links, string player1abilities, string player2abilities); // Initializes the Game
    Player* getActivePlayer();
    void switchActivePlayer(); // Changes the "active" player
    void toggleEnhancementsOn();
    Player* getWinningPlayer();
    Player* getInactivePlayer();
    void runSequence(string filename, bool graphicsOn); // Runs a command sequence
};

#endif
