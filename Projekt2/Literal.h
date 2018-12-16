#ifndef LITERAL_H
#define LITERAL_H

#include <string>

class Literal
{
    private:
        std::string name;
        bool bel;
        Literal *nachfolger;
    public:
        Literal();
        Literal(string a, bool b):name(a),bel(b)
        {
            nachfolger=0;
        }
        virtual ~Literal();
        void set_bel(bool);


};

#endif // LITERAL_H
