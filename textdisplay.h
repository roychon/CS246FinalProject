#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include "observer.h"
#include <vector>
using namespace std;

class TextDisplay : public Observer {
    vector<vector<Cell>> grid;
    const int gridSize;

public:
    TextDisplay(int n);
    void notify(Cell &c) override;
    ~TextDisplay();
};

#endif
