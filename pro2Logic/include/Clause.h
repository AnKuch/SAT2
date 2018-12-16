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
    Clause *suc;
public:
    Clause(int b):number(b)
    {
        suc = 0;
    }
    Clause *next();
    int get_nr();
    vector<int> get_lit();
    void set_lit(vector<int>);
};

#endif // CLAUSE_H
