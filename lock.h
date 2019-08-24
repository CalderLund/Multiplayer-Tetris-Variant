#ifndef _LOCK_H_
#define _LOCK_H_

#include "specaction.h"

class Lock: public SpecAction {
    public:
        Lock(Action *);
        int clockwise(Block *) override;
        int cclockwise(Block *) override;
};

#endif