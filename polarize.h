#ifndef __POLARIZE_H__
#define __POLARIZE_H__
#include "ability.h"
using namespace std;

class Polarize : public Ability {
    vector<vector<Cell>> *grid;
    public:
        Polarize(Type type, vector<vector<Cell>> *grid);
        void apply() override;
        bool checkValid() override;
        char getType() override;
};

#endif
