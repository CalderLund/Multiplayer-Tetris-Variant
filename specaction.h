#ifndef _SPECACTION_H
#define _SPECACTION_H

#include "action.h"

class SpecAction: public Action {
    protected:
        Action *currAct;
    public:
        SpecAction(Action *);
        char printchar() override; 
        int left(Block *) override;
        int right(Block *) override;
        int down(Block *) override;
        void drop(Block *) override;
        int clockwise(Block *) override;
        int cclockwise(Block *) override;
        virtual ~SpecAction() = 0;
};

#endif
