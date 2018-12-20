#include "Clauselist.h"
#include <iostream>

Clause *Clauselist::begin(){return start;}

void Clauselist::insert(Clause *k)
{
    k->suc = start;
    start = k;
}

Clause* Clauselist::findl(int nam)
{
    Clause *fin;
    for (fin = begin(); fin != 0; fin = fin->next())
        if (fin->get_nr() == nam)
            break;
    return fin;
}

void Clauselist::remove(int nam)
{
    if(start!=0)
    {
        if(start->get_nr() == nam)
        {
            start = start->next();
        }
        else if(start->get_nr() != nam && start->next() == 0)
        {
            return;
        }
        else
        {
            Clause *fin;
            for (fin = begin(); fin != 0; fin = fin->next())
            {
                if(fin->next()->get_nr() != nam && fin->next()->next() == 0)
                    break;
                else if (fin->next()->get_nr() == nam)
                {
                    fin->suc = fin->next()->next();
                    break;
                }
            }
        }
    }
}

bool Clauselist::empty() { return start == 0; }
