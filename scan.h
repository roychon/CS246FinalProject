#ifndef __SCAN_H__
#define __SCAN_H__

#include "ability.h"
#include "link.h"
using namespace std;

class Scan : public Ability {
    vector<vector<Cell>> *grid;
    Link *target;
    public:
        Scan(Type type, vector<vector<Cell>> *grid);
        void apply() override;
        bool checkValid() override;
        char getType() override;
        void setTarget(Link *target);
};

#endif