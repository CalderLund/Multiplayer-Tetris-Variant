#ifndef _NORMAL_H
#define _NORMAL_H

#include "action.h"

class Normal: public Action {
    public:
        char printchar() override; 
        int left(Block *) override;
        int right(Block *) override;
        int down(Block *) override;
        void drop(Block *) override;
        int clockwise(Block *) override;
        int cclockwise(Block *) override;
};

#endif
