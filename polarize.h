#ifndef __POLARIZE_H__
#define __POLARIZE_H__
#include "ability.h"
#include "link.h"

class Polarize : public Ability {
    public:
        void apply(Link &link) override;
};

#endif