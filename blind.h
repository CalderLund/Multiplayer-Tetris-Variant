#ifndef _BLIND_H
#define _BLIND_H

#include "specaction.h"

class Blind: public SpecAction {
    public:
        Blind(Action *);
        char printchar() override;
};

#endif
