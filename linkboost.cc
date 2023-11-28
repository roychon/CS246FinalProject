#include "linkboost.h"

void LinkBoost::apply(Link &link) {
    link.getMoveFactor() += 1;
}
