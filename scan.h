#ifndef __SCAN_H__
#define __SCAN_H__
#include "ability.h"
#include "link.h"

class Scan : public Ability {
    public:
        void apply(Link &link) override;
};

#endif