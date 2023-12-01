#ifndef __SCAN_H__
#define __SCAN_H__
#include "ability.h"
#include "link.h"

class Scan : public Ability {
    vector<vector<Cell>> *grid;
    public:
        Scan(vector<vector<Cell>> *grid);
        void apply(int x, int y) override;
        bool checkValid(int x, int y) override;
        char getType() override;
};

#endif