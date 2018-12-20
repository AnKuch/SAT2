#ifndef CLAUSELIST_H
#define CLAUSELIST_H
#include "Clause.h"

class Clauselist
{
private:
    Clause *start;
public:
    Clauselist()
    {
        start=0;
    }
    Clause *begin();
    void insert(Clause *);
	Clause* findl(int);
	void remove(int);
	bool empty();
};

#endif // CLAUSELIST_H
