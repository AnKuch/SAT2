#include "Literal.h"

int Literal::get_nr(){return number;}
void Literal::set_pos(Clause *i)
{
    int x = i->get_nr();
    poso.push_back(x);
}
vector <int>Literal::get_pos()
{
    return poso;
}
void Literal::set_neg(Clause *i)
{
    int x = i->get_nr();
    nego.push_back(x);
}
vector <int>Literal::get_neg()
{
    return nego;
}
void Literal::set_value(int i)
{
    value=i;
}
int Literal::get_value()
{
    return value;
}

Literal *Literal::next(){return suc;}
