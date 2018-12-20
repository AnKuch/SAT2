#ifndef LITERAL_H
#define LITERAL_H
#include <vector>
#include "Clause.h"
#include "Clauselist.h"

class Literal
{
friend class Literallist;
private:
    int number;
    int value;
    vector<int> poso;
    vector<int> nego;
    Literal *suc;
public:
    Literal(int a):number(a)
    {
        value=2;
        suc=0;
    }
    int get_nr();
    void set_value(int);
    int get_value();
    void set_pos(Clause*);
    vector <int>get_pos();
    void set_neg(Clause*);
    vector <int>get_neg();
    Literal *next();
};

#endif // LITERAL_H
