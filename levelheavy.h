#ifndef _LEVELHEAVY_H
#define _LEVELHEAVY_H

#include "specaction.h"

class LevelHeavy: public SpecAction {
    public:
        LevelHeavy(Action *);
        int left(Block *) override;
        int right(Block *) override;
        int clockwise(Block *) override;
        int cclockwise(Block *) override;
};

#endif
