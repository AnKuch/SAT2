#include "Clause.h"


Clause *Clause::next(){return suc;}
int Clause::get_nr(){return number;}
vector<int> Clause::get_lit(){return x;}
void Clause::set_lit(vector<int> i){x=i;}
