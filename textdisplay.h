#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include <vector>
using namespace std;
class Cell;

class TextDisplay : public Observer {
    vector<vector<char>> grid;
    const int gridSize;

public:
    TextDisplay();
    void notify(Cell &c) override;
    ~TextDisplay();

    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td); 
};

#endif
