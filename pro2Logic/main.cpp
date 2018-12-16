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
vector<int> listl;
int clacount = 1;
vector<int> listbel;

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
        cout << "weiter" << endl;
        return true;
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
                Clause *clause = new Clause(clacount);
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
/*         if ( file.eof ( ) )
 *         {
 *             cout << "\n";
 *             cout << "CNF_DATA_READ - Fatal error!\n";
 *             cout << "  Error3 while reading the file.\n";
 *             exit ( 1 );
 *         }
 *
 *         if ( line[0] == 'c' || line[0] == 'C' )
 *         {
 *             cout << "C linie" << endl;
 *             continue;
 *         }
 *         if (0 == lastblank ( line ))
 *         {
 *             cout << "leere linie" << endl;
 *             continue;
 *         }
 *
 *             // expecting line p cnf numVal numCla
 *         if ( line[0] != 'p' && line[0] != 'P' )
 *         {
 *             cout << "\n";
 *             cout << "CNF_DATA_READ - Fatal error!\n";
 *             cout << "The first non-blank and non-comment line does not start with 'p'." << endl;
 *             exit ( 1 );
 *         }
 *         if ( line[1] != ' ' )
 *         {
 *             cout << "\n";
 *             cout << "CNF_DATA_READ - Fatal error!\n";
 *             cout << "'p' must be followed by a whitespace." << endl;
 *             exit ( 1 );
 *         }
 *         //
 *         //  Remove the first two characters and shift left.
 *         //
 *
 *         line[0] = ' ';
 *         line[1] = ' ';
 *         line = stAdjust ( line );
 *         //
 *         //  Expect the string 'CNF'
 *         //
 *         if ((line[0] == 'c' ) && ( line[1] == 'n' ) && ( line[2] == 'f' ) )
 *         {
 *             cout << line[0] << endl;
 *         }
 *         else
 *         {
 *             cout << "\n";
 *             cout << "CNF_DATA_READ - Fatal error!\n";
 *             cout << "'p ' must be followed by 'cnf'";
 *             exit ( 1 );
 *         }
 *         if (line[3] != ' ')
 *         {
 *             cout << "\n";
 *             cout << "CNF_DATA_READ - Fatal error!\n";
 *             cout << "'p cnf' must be followed by a whitespace.";
 *             exit(1);
 *         }
 *         //
 *         //  Remove the first two characters and shift left.
 *         //
 *         line[0] = ' ';
 *         line[1] = ' ';
 *         line[2] = ' ';
 *         line[3] = ' ';
 *         line = stAdjust (line);
 *
 *         //Reads next word (= number of variables)
 *         sscanf(line.c_str(), "%d %d", &numVal, &numCla);
 *
 *         cout << "NumVal: " << numVal << "NumCla: " << numCla << endl;
 *     }
 */

//        //Reads rest of lines (ignores '0')
//
//        numLit = 0;
//        numCla =0;
//        numLitCla=0;
//
//        while(1)
//        {
//            getline(file, line);
//            if(file.eof())
//            {
//                break;
//            }
//            if(line[0] == 'c' || line[0] == 'C')
//            {
//                continue;
//            }
//            if(lengNonBl(line) == 0)
//            {
//                continue;
//            }
//            while(1)
//            {
//                extractFirst(line, word, rest);
//                line = rest;
//                if(lengNonBl(word) <= 0)
//                {
//                    break;
//                }
//                valList = retIntFromString(word, &length, &error);
//                if(error)
//                {
//                    break;
//                }
//                if ( valList != 0 )
//                {
//                    valList2[numLit] = valList;
//                    numLit = numLit + 1;
//                    numLitCla = numLitCla + 1;
//                }
//                else
//                {
//                    numLitCla2[numCla] = numLitCla;
//                    numCla = numCla + 1;
//                    numLitCla = 0;
//                }
//            }
//        }
//        cout << numCla << endl;
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
        listl.push_back(l);
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
        cout << "neues s: " << s<< endl;
        cout << "Ende readClauses" << endl;
        int s = c->get_lit()[0];
        cout << "s: " << s << endl;

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
            cout << "s2[i]: " << s2[i] << endl;
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
