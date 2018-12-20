#include "Clause.h"


Clause *Clause::next(){return suc;}
int Clause::get_nr(){return number;}
vector<int> Clause::get_lit(){return x;}
void Clause::set_lit(vector<int> i){x=i;}
void Clause::set_numberAct(int i){numberAct=numberAct+i;}
int Clause::get_numberAct(){return numberAct;}
void Clause::set_flag(int i){flag=i;}
int Clause::get_flag(){return flag;}
