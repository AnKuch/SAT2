#include "FileRead.h"
#include <fstream>
#include <iostream>
#include <fstream>

using namespace std;

std::fstream file;
std::string line;
std::string word;
std::string rest;
int numVal; //number of variables
int numCla; //number of clauses
int numLit; //number of signed literals
int numLitCla; //number of signed literal occurring in each clause
int valList; //list of all signed literals in all clauses (ordered by clauses)
std::vector <int> valList2;
std::vector <int> numLitCla2;
bool error;
int length;

bool cnfRead(std::string filename)
{
    file.open(filename);

    if(!file)
    {
        cout << "\n";
        cout << "CNF_DATA_READ - Fatal error!\n";
        cout << "  Could not open file.\n";
        exit ( 1 );
    }
    else
    {
       while (1)
        {
            getline(file,line);
            if ( file.eof ( ) )
            {
                cout << "\n";
                cout << "CNF_DATA_READ - Fatal error!\n";
                cout << "  Error3 while reading the file.\n";
                exit ( 1 );
            }

            if ( line[0] == 'c' || line[0] == 'C' )
            {
                continue;
            }
            if ( 0 < lastblank ( line ) )
            {
                break;
            }
        }
            // expecting line p cnf numVal numCla
        if ( line[0] != 'p' && line[0] != 'P' )
        {
            cout << "\n";
            cout << "CNF_DATA_READ - Fatal error!\n";
            cout << "The first non-blank and non-comment line does not start with 'p'." << endl;
            exit ( 1 );
        }
        if ( line[1] != ' ' )
        {
            cout << "\n";
            cout << "CNF_DATA_READ - Fatal error!\n";
            cout << "'p' must be followed by a whitespace." << endl;
            exit ( 1 );
        }
        //
        //  Remove the first two characters and shift left.
        //

        line[0] = ' ';
        line[1] = ' ';
        line = stAdjust ( line );
        //
        //  Expect the string 'CNF'
        //
        if ((line[0] == 'c' ) && ( line[1] == 'n' ) && ( line[2] == 'f' ) )
        {
            cout << line[0] << endl;
        }
        else
        {
            cout << "\n";
            cout << "CNF_DATA_READ - Fatal error!\n";
            cout << "'p ' must be followed by 'cnf'";
            exit ( 1 );
        }
        if (line[3] != ' ')
        {
            cout << "\n";
            cout << "CNF_DATA_READ - Fatal error!\n";
            cout << "'p cnf' must be followed by a whitespace.";
            exit(1);
        }
        //
        //  Remove the first two characters and shift left.
        //
        line[0] = ' ';
        line[1] = ' ';
        line[2] = ' ';
        line[3] = ' ';
        line = stAdjust ( line );

        //Reads next word (= number of variables)
        sscanf(line.c_str(), "%d %d", &numVal, &numCla);

        //Reads rest of lines (ignores '0')

        numLit = 0;
        numCla =0;
        numLitCla=0;

        while(1)
        {
            getline(file, line);
            if(file.eof())
            {
                break;
            }
            if(line[0] == 'c' || line[0] == 'C')
            {
                continue;
            }
            if(lengNonBl(line) == 0)
            {
                continue;
            }
            while(1)
            {
                extractFirst(line, word, rest);
                line = rest;
                if(lengNonBl(word) <= 0)
                {
                    break;
                }
                valList = retIntFromString(word, &length, &error);
                if(error)
                {
                    break;
                }
                if ( valList != 0 )
                {
                    valList2[numLit] = valList;
                    numLit = numLit + 1;
                    numLitCla = numLitCla + 1;
                }
                else
                {
                    numLitCla2[numCla] = numLitCla;
                    numCla = numCla + 1;
                    numLitCla = 0;
                }
            }
        }
        cout << numCla << endl;
        file.close();
        return error;
    }
}


//Return (string s, int *last, bool *error)
int retIntFromString (string s, int *last, bool *error)
{
    char c;
    int state = 0;
    int vsign;
    int val;

    for (int i=0; i<= s.length(); i++)
    {
        c = s[i];
        // checks the sign
        if(state == 0)
        {
            if(c == ' ')
            {
            }
            else if(c == '-')
            {
                state = 1;
                vsign = -1;
            }
            else if(c == '+')
            {
                state = 1;
                vsign = +1;
            }
            else if('0'<=c && c<='9')
            {
                state = 2;
                val = (int)c;
            }
            else
            {
                *error = true;
                return val;
            }
        }
        // checks the first digit
        else if(state == 1)
        {
            if(c == ' ')
            {
            }
            else if('0'<=c && c<='9')
            {
                state == 2;
                val = (int)c;
            }
            else
            {
                *error = true;
                return val;
            }
        }
        // checks the second digit if necessary
        else if(state == 2)
        {
            if('0'<=c && c<='9')
            {
                val = (int)(10 * val + c);
            }
            else
            {
                val = vsign * val;
                *last = i - 1;
                return val;
            }
        }
    }
    if(state == 2)
    {
        val = vsign * val;
        *last = lengNonBl(s);
    }
    else
    {
        *error = true;
        return val;
    }
    return val;
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

// Checks if a string is blank (the case if n=0)
int lastblank ( string s )
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
    cout << "in Adjust" << endl;
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
