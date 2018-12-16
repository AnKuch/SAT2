#include "Literallist.h"

Literal *Literallist::begin(){return start;}

void Literallist::insert(Literal *k)
{
    k->suc = start;
    start = k;
}

Literal* Literallist::findl(int nam)
{
    Literal *fin;
    for (fin = begin(); fin != 0; fin = fin->next())
        if (fin->get_nr() == nam)
            break;
    return fin;
}

void Literallist::remove(int nam)
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
            Literal *fin;
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

bool Literallist::empty() { return start == 0; }
