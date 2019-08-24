#ifndef _SPECHEAVY_H
#define _SPECHEAVY_H

#include "specaction.h"

class SpecHeavy: public SpecAction {
    public:
        SpecHeavy(Action *);
        int right(Block *) override;
        int left(Block *) override;
};

#endif
