#include <iostream>
#include <fstream>
#include <vector>
#include "Clauselist.h"
#include "Literallist.h"

using namespace std;

int lastblank(string);
int retIntFromString (string, bool *);
int lengNonBl (string);
string stAdjust (string);
void extractFirst (string, string &, string &);
void readfile(string);
void readClauses(string, Clause*);
bool solve();
bool emptClause();
void set_belToClauses(Clause *);
void unit_propagation();
void litSet(int);

std::string word;
std::string rest;
int numVal; //number of variables
int numCla; //number of clauses
int numLit; //number of signed literals
std::vector <int> valList2;
std::vector <int> numLitCla2;
bool error =false;
int length;
Clauselist listc;
Literallist listl;
int clacount = 0;
int litcount = 0;
vector<int> listbel;
vector<pair<string,int>> aktivities;

int main()
{
    string filename;
    string line;
    cout << "Welcome to the DPLL SAT Solver" << endl;
    cout << "What cnf file would you like to be solved?" << endl;
    cin >> filename;

    readfile(filename);
    solve();

    return 0;
}

bool solve()
{
    if(listc.begin()==0)
    {
        cout << "CNF is satisfiable" << endl;
        return true;
    }
    else if(emptClause())
    {
        cout << "CNF is unsatisfiable" << endl;
        return false;
    }
    else
    {
        unit_propagation();
        while(1)
        {
            Clause *object;
            int li;
            //Finden der kleinsten Klausel
            for(int i=2;i<=numVal;i++)
            {
                int ret=false;
                for(object=listc.begin();object!=0;object=object->next())
                {
                    int x = object->get_numberAct();
                    if(x==i)
                    {
                        li= object->get_lit()[0];
                        ret = true;
                        break;
                    }
                    else continue;
                }
                if(ret)
                {
                    break;
                }
            }
            litSet(li);
            aktivities.push_back(make_pair("chooseLi",li));
            unit_propagation();
            for(int i=2;i<=numVal;i++)
            {
                int ret=false;
                for(object=listc.begin();object!=0;object=object->next())
                {
                    int x = object->get_numberAct();
                    if(x==i)
                    {
                        li= object->get_lit()[0];
                        ret = true;
                        break;
                    }
                    else continue;
                }
                if(ret)
                {
                    break;
                }
            }
            litSet(li);
            unit_propagation();
            cout << "aktivities: " << aktivities[0].first << ": " <<aktivities[0].second << endl;
            cout << "aktivities: " << aktivities[1].first << ": " <<aktivities[1].second << endl;
            cout << "aktivities: " << aktivities[2].first << ": " <<aktivities[2].second << endl;
            break;
        }
        return true;
    }
}

/*
Unitpropagation:
Finden von Clauses mit nur einem aktiven Literal
Wenn gefunden:
- Finden des aktiven Literals: unitcl (= pos/neg)
- Gefundenes Literal in aktivierte Belegung speichern(listbel)
- Variable herausfinden: positive Zahl von unitcl (= val)
- Finden von Caluses, in denen unitcl neg vor kommt
	- wenn unitcl = neg => clauses auf set u. Flag = val
	- wenn unitcl = pos => aktive lit in clauses -1
- Finden von Clauses, in denen unitcl pos vor kommt.
	- wenn unitcl = pos => clauses auf set u. Flag = val
	- wenn unitcl = neg => aktive lit in clauses -1
- unitpropagation in aktivities speichern
*/
void unit_propagation()
{
    Clause *object;
    int unitcl;
    bool ret=false;
    //Finden von Clauses mit nur einem aktiven Literal
    for(object=listc.begin();object!=0;object=object->next())
    {
        if(object->get_numberAct()==1)
        {
            //Finden des aktiven Literals: unitcl
            for(int i=0; i<=(object->get_lit().size());i++)
            {
                int x = object->get_lit()[i];
                for(int j= 0; j<=listbel.size();j++)
                {
                    if(x!=listbel[j])
                    {
                        unitcl=x;
                        litSet(unitcl);
                        ret = true;
                        break;
                    }
                    else continue;
                }
                if(ret) break;
            }
            aktivities.push_back(make_pair("unitp",unitcl)); //unitpropagation in aktivities speichern
        }
        else continue;
    }
}

void litSet(int cl)
{
    //Gefundenes Literal in aktivierte Belegung speichern(listbel)
    listbel.push_back(cl);
    int val; //Variable herausfinden: positive Zahl von unitcl (= val)
    if(cl<0) val=cl*(-1);
    else val=cl;
    Literal *objectl;
    for(objectl=listl.begin();objectl!=0;objectl=objectl->next())
    {
        if(objectl->get_nr()==val)
        {
            //unitcl = neg
            if(cl<0)
            {
                objectl->set_value(0);
                Clause *objectc;
                for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                {
                    int x = objectc->get_nr();
                    //Finden von Caluses, in denen unitcl neg vor kommt
                    for(int i=0;i<=objectl->get_neg().size();i++)
                    {
                        int y=objectl->get_neg()[i];
                        if(x==y)
                        {
                            objectc->set_flag(val); //clauses auf set u. Flag = val
                        }
                        else continue;
                    }
                    //Finden von Clauses, in denen unitcl pos vor kommt.
                    for(int i=0;i<=objectl->get_pos().size();i++)
                    {
                        int y=objectl->get_pos()[i];
                        if(x==y)
                        {
                            objectc->set_numberAct(-1); //aktive lit in clauses -1
                        }
                        else continue;
                    }
                }
                break;
            }
            //unitcl = pos
            else if(cl>0)
            {
                objectl->set_value(1);
                Clause *objectc;
                for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                {
                    int x = objectc->get_nr();
                    //Finden von Clauses, in denen unitcl pos vor kommt.
                    for(int i=0;i<=objectl->get_pos().size();i++)
                    {
                        int y=objectl->get_pos()[i];
                        if(x==y)
                        {
                            objectc->set_flag(val);//clauses auf set u. Flag = val
                        }
                        else continue;
                    }
                    //Finden von Caluses, in denen unitcl neg vor kommt
                    for(int i=0;i<=objectl->get_neg().size();i++)
                    {
                        int y=objectl->get_neg()[i];
                        if(x==y)
                        {
                            objectc->set_numberAct(-1); //aktive lit in clauses -1
                        }
                        else continue;
                    }
                }
                break;
            }
            else
            {
                cout << "Error in Clauses!" << endl;
                break;
            }
        }
        else continue;
    }
}

bool emptClause()
{
    Clause *object;
    for(object=listc.begin();object!=0;object=object->next())
    {
        vector<int> x = object->get_lit();
        if(x.size()==0)
        {
            return true;
        }
    }
    return false;
}

void readfile(string a)
{
    string line;
    ifstream file;
    ofstream file2;
    file.open(a,ios_base::in);
    while(getline(file,line))
    {
        cout << "line: " << line << endl;
        if(line.length()>=1)
        {
            if(line[0]=='c'||line[0]=='C')
            {
                continue;
            }
            else if(line[0] == '-' || (line[0] > '0' && line[0]<='9'))
            {
                Clause *clause = new Clause(clacount+1);
                clacount++;
                listc.insert(clause);
                readClauses(line, clause);
            }

            else if((line[0]=='p'||'P') && line[1] ==' ' && (line[2]=='c'||'C') && (line[3]=='n'||'N') && (line[4]=='f'||'F') && line[5]==' ')
            {
                line[0] = ' ';
                line[1] = ' ';
                line[2] = ' ';
                line[3] = ' ';
                line[4] = ' ';
                line = stAdjust (line);
                numVal = retIntFromString(line, &error);
                if(error)
                {
                    cout << "Error in line 'p cnf Var Cla'" << endl;
                    break;
                }
                else
                {
                    if(numVal > 9)
                    {
                        line[0] = ' ';
                        line[1] = ' ';
                        line = stAdjust (line);
                    }
                    else
                    {
                        line[0] = ' ';
                        line = stAdjust (line);
                    }
                }
                numCla = retIntFromString(line, &error);
                for (int i=0;i<=numVal; i++)
                {
                    Literal *object = new Literal(i);
                    listl.insert(object);
                }
                if(error)
                {
                    cout << "Error in line 'p cnf Var Cla'" << endl;
                    break;
                }
                else continue;
            }
            Clause *object;
            file2.open("testout.txt", ios_base::out);
            for(object=listc.begin();object!=0;object=object->next())
            {
                vector<int>x= object->get_lit();
                for(int i=0; i<x.size();i++)
                {
                    file2 << ' ' << x[i];
                }
                file2 << '\n';
            }
            file2.close();
        }
    }
        file.close();
}

void readClauses(string s, Clause *c)
{
    while(1)
    {
        if(s[0]=='0')
        {
            break;
        }
        int l = retIntFromString(s, &error);
        c->set_numberAct(1);
        int val;
        if(l<0)val=l*(-1);
        else val=l;
        vector<int>x=c->get_lit();
        x.push_back(l);
        c->set_lit(x);
        if(l<-9)
        {
            s[0] =' ';
            s[1] =' ';
            s[2] =' ';
        }
        else if(l>9 || l<0)
        {
            s[0] =' ';
            s[1] =' ';
        }
        else
        {
            s[0]=' ';
        }
        s=stAdjust(s);
        Literal *object;
        for(object=listl.begin();object!=0;object=object->next())
        {
            if(object->get_nr()==val)
            {
                if(l<0)
                {
                    object->set_pos(c);
                }
                else if(l>0)
                {
                    object->set_neg(c);
                }
                else
                {
                    cout << "no value in this clause" << endl;
                    break;
                }
            }
        }
    }
}

int lastblank(string s)
{
    int n;
    n = s.length();
    while (0 < n)
    {
        if(s[n-1]!= ' ')
        {
            return n;
        }
        n--;
    }
  return n;
}

//Return (string s, bool *error)
int retIntFromString (string s, bool *error)
{
    char c;
    int state = 0;
    int vsign;
    int val;

    for (int i=0; i<= s.length(); i++)
    {
        c=s[i];
        if(state == 0)
        {
            if(c==' ') continue;
            else if (c=='-')
            {
                state = 1;
                vsign = -1;
            }
            else if (c>'0' && c<='9')
            {
                val=atoi(&c);
                vsign = 1;
                state = 2;
            }
            else
            {
                cout << "erster error" << endl;
                *error=true;
                return 0;
            }
        }
        else if(state == 1) //negative digit
        {
            if(c==' ') continue;
            if(c>'0' && c<='9')
            {
                val=atoi(&c);
                state=2;
            }
            else
            {
                cout << "zweiter error" << endl;
                *error=true;
                return 0;
            }
        }
        else if(state ==2) //first digit read
        {
            if(c>='0' && c<='9') //second digit
            {
                val=vsign*10*val + atoi(&c);
                return val;
            }
            else if (c==' ')
            {
                val = vsign*val;
                return val;
            }
            else
            {
                cout << "dritter error" << endl;
                *error = true;
                return 0;
            }
        }

    }
}

int lengNonBl (string s)
{
    int n;

    n = s.length ( );

    while ( 0 < n )
    {
        if ( s[n-1] != ' ' )
        {
        return n;
        }
        n = n - 1;
    }
    return n;
}


// Adjusts a string to the left
string stAdjust ( string s1 )
{
    int i;
    string s2;
    int nonblank;
    char TAB = 9;

    s2 = s1;
    if ( s2.length() <= 0 )
    {
        return s2;
    }
    nonblank = 0;

    for ( i = 0; i < s2.length(); i++ )
    {
        if ( s1[i] != ' ' && s1[i] != TAB )
        {
            nonblank = i;
            break;
        }
    }
    if ( 0 < nonblank )
    {
        for ( i = 0; i < s2.length() - nonblank; i++ )
        {
            s2[i] = s1[i+nonblank];
        }
        for ( i = s2.length() - nonblank; i < s2.length(); i++ )
        {
            s2[i] = ' ';
        }

    }
    return s2;
}

// Extracts the first word of a string
void extractFirst (string s, string &s1, string &s2)
{
    int i;
    int mode;
    s1 = "";
    s2 = "";
    mode = 1;

    cout << s << endl;
    for ( i = 0; i < s.length(); i++ )
    {
        if ( mode == 1 )
        {
            if ( s[i] != ' ' )
            {
                mode = 2;
            }
        }
        else if ( mode == 2 )
        {
            if ( s[i] == ' ' )
            {
                mode = 3;
            }
        }
        else if ( mode == 3 )
        {
            if ( s[i] != ' ' )
            {
                mode = 4;
            }
        }
        if ( mode == 2 )
        {
            s1 = s1 + s[i];
        }
        else if ( mode == 4 )
        {
            s2 = s2 + s[i];
        }
    }

    return;
}
