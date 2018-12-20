#ifndef CLAUSE_H
#define CLAUSE_H
#include <vector>

using namespace std;

class Clause
{
friend class Clauselist;
private:
    int number;
    vector<int>x;
    int numberAct;
    int flag;
    Clause *suc;
public:
    Clause(int b):number(b)
    {
        suc = 0;
        numberAct=0;
        flag = 0;
    }
    Clause *next();
    int get_nr();
    vector<int> get_lit();
    void set_lit(vector<int>);
    void set_numberAct(int);
    int get_numberAct();
    void set_flag(int);
    int get_flag();
};

#endif // CLAUSE_H
