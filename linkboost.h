#ifndef __LINKBOOST_H__
#define __LINKBOOST_H__
#include "ability.h"
#include "link.h"
class LinkBoost : public Ability {
    public:
        void apply(Link &link) override; // TODO: edit move function so it takes into account moveFactor when calculating whether or not is a valid move
};

#endif