#ifndef LITERALLIST_H
#define LITERALLIST_H
#include "Literal.h"


class Literallist
{
    private:
    Literal *start;
public:
    Literallist()
    {
        start = 0;
    }
    Literal *begin();
    void insert(Literal *);
	Literal* findl(int);
	void remove(int);
	bool empty();
};

#endif // LITERALLIST_H
