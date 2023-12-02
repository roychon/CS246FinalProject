#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "cell.h"
#include "window.h"
using namespace std;

class GraphicsDisplay : public Observer {
    Xwindow xw;
    vector<vector<char>> grid;
    Player *activePlayer;
    protected:
    bool enhancementsOn;

public:

  GraphicsDisplay(Xwindow &xw);
  void notify(Cell &c) override;
  void toggleenhancementsOn();
  void setActivePlayer(Player *player);

  ~GraphicsDisplay();
};
#endif
