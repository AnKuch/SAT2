#ifndef LITERAL_H
#define LITERAL_H


class Literal
{
friend class Literallist;
private:
    int number;
    Literal *suc;
public:
    Literal(int a):number(a)
    {
        suc=0;
    }
    int get_nr();

    Literal *next();
};

#endif // LITERAL_H
