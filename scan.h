#ifndef __SCAN_H__
#define __SCAN_H__

#include "ability.h"
using namespace std;

class Scan : public Ability {
    vector<vector<Cell>> *grid;
    public:
        Scan(Type type, vector<vector<Cell>> *grid);
        void apply() override;
        bool checkValid() override;
        char getType() override;
};

#endif