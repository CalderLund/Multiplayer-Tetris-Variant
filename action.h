#ifndef _ACTION_H
#define _ACTION_H

class Block;

class Action {
    public:
        virtual char printchar() = 0;
        virtual int left(Block *) = 0;
        virtual int right(Block *) = 0;
        virtual int down(Block *) = 0;
        virtual void drop(Block *) = 0;
        virtual int clockwise(Block *) = 0;
        virtual int cclockwise(Block *) = 0;
	virtual ~Action() {};
};

#endif
