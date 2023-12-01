#include "polarize.h"

void Polarize::apply(Link &link) {
    link.setType(link.getType() == 'D' ? 'V' : 'D');
}
