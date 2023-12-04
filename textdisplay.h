#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include "player.h"
#include <iostream>
#include <vector>
using namespace std;
class Cell;

class TextDisplay : public Observer {
    vector<vector<char>> grid;
    const int gridSize;
    Player *activePlayer;
    protected:
    bool enhancementsOn;

public:
    TextDisplay();
    void notify(Cell &c) override;
    void setActivePlayer(Player *player);
    ~TextDisplay();
    void toggleEnhancementsOn();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td); 
};

#endif
