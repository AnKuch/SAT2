/***************************************************************
 * Name:      test1002App.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2018-11-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "test1002App.h"
#include "test1002Main.h"


using namespace std;

int retIntFromString (string, bool *);
string stAdjust (string);
void readfile(string);
void readClauses(string, Clause*);
void solve();
bool emptClause();
void unit_propagation();
void litSet(int);
void set_val();
bool check_conflicts();
void backtrack();
void handle_confilcts();
void unset(int);
void check_pure_literals();

int numVal; //number of variables
int numCla; //number of clauses
bool error =false;
Clauselist listc;
Literallist listl;
int clacount = 0;
vector<int> listbel;
vector<pair<string,int>> activities;
bool unsatisfiable;
bool satisfiable;
int setCl;
typedef std::chrono::high_resolution_clock Clock;


std::vector<int> solver(string filename,string dir,string *result)
{
    cout << "Welcome to the DPLL SAT Solver" << endl;
    cout << "What cnf file would you like to be solved?" << endl;
    cin >> filename;
    auto t1 = Clock::now();
    readfile(filename);
    Literal *objectl;

    solve();
    auto t2 = Clock::now();
    std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1);
    if(unsatisfiable)
    {
        return listbel;
        *result = "unsatisfiable";
    }
    else if(satisfiable)
    {
        vector <int> outputL;
        cout << "Satifiable"<< endl<< endl;
        cout << "Possible solution: " << endl << endl;
        for(objectl=listl.begin();objectl!=0;objectl=objectl->next())
        {
            int x = objectl->get_nr();
            if(objectl->get_value()==0)
            {
                x=(-1)*x;
                outputL.push_back(x);
            }
            else
            {
                outputL.push_back(x);
            }
        }
        return outputL;
        *result = "satisfiable";
    }
    else
    {
        return listbel;
        *result = "noResult";
    }
    fstream fw;
    ifstream fr;
    bool write = true;
    fr.open("benchs.txt",ios_base::in);
    if(!fr)
    {
        cout << "ERROR: No Benchmarkfile" << endl;
        system("pause");
    }
    else
    {
        string line;
        while(getline(fr,line))
        {
            string s = filename;
            std::stringstream st;
            for(int i=0; i<s.length();i++)
            {
                st << line[i];
            }
            if(st.str()==s)
            {
                write = false;
                break;
            }
            else write = true;
        }
    }
    fr.close();
    if(write)
    {
        fw.open("benchs.txt",ios_base::in | ios_base::out | ios::ate);
        if(!fw)
        {
            cout << "ERROR: No Benchmarkfile" << endl;
            system("pause");
        }
        else
        {
            fw << filename << ' ' << duration.count() << " Nanoseconds\n" ;
        }
        fw.close();
    }
    else cout << "Bereits gespeichert!" << endl;
    system("pause");
}

void solve()
{
        unit_propagation();
        check_pure_literals();
        while(satisfiable==false && unsatisfiable==false)
        {
            set_val();
            unit_propagation();
            handle_confilcts();
            if(setCl==numCla) satisfiable=true;
        }

}

void check_pure_literals()
{
    Literal *object;
    for(object=listl.begin();object!=0;object=object->next())
    {
        if(object->get_value()==2)
        {
            if(object->get_pos().empty())
            {
                if(!object->get_neg().empty())
                {
                    int x = object->get_nr()*(-1);
                    cout << "literal pure " << x << endl;
                    litSet(x);
                    activities.push_back(make_pair("pureLit",x));
                }
                else continue;
            }
            else if(object->get_neg().empty())
            {
                if(!object->get_pos().empty())
                {
                    int x = object->get_nr();
                    cout << "literal pure " << x << endl;
                    litSet(x);
                    activities.push_back(make_pair("pureLit",x));
                }
                else continue;
            }
        }
        else continue;
    }
}


void handle_confilcts()
{
    if(check_conflicts())
    {
        backtrack();
    }
}

void unset(int var)
{
    if(var>0) var=var;
    else var= var*(-1);
    Literal *objectl;
    Clause *objectc;
    for(objectl=listl.begin();objectl!=0;objectl=objectl->next())
    {
        int vardel=objectl->get_nr();
        if(var==vardel)
        {
            if(objectl->get_value()==1)
            {
                int s = objectl->get_pos().size();
                for(int x=0;x<s;x++)
                {
                    int posOc = objectl->get_pos()[x];
                    for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                    {
                        if(objectc->get_flag()==var)
                        {
                            int valClSet = objectc->get_nr();
                            if(posOc==valClSet && objectc->get_flag()==var)
                            {
                                objectc->set_flag(0);
                                setCl--;
                            }
                            else continue;
                        }
                        else continue;
                    }
                }
                s = objectl->get_neg().size();
                for(int x=0;x<s;x++)
                {
                    int negOc = objectl->get_neg()[x];
                    for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                    {
                        if(negOc==objectc->get_nr())
                        {
                            if(objectc->get_flag()==0)
                            {
                                objectc->set_numberAct(1);
                            }
                        }
                    }
                }
            }
            else if(objectl->get_value()==0)
            {
                int s = objectl->get_neg().size();
                for(int x=0;x<s;x++)
                {
                    int negOc = objectl->get_neg()[x];
                    for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                    {

                            int valClSet = objectc->get_nr();
                            if(negOc==valClSet && objectc->get_flag()==var)
                            {
                                objectc->set_flag(0);
                                setCl--;
                            }
                            else continue;
                    }
                }
                s= objectl->get_pos().size();
                for(int x=0;x<s;x++)
                {
                    int posOc = objectl->get_pos()[x];
                    for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                    {
                        if(posOc==objectc->get_nr())
                        {
                            if(objectc->get_flag()==0)
                            {
                                objectc->set_numberAct(1);
                            }
                        }
                    }
                }
            }
            objectl->set_value(2);
            int s = listbel.size();
            for(int i=0; i<s;i++)
            {
                if(listbel[i]==var) listbel.erase(listbel.begin()+i);
            }
        }
    }
}


/*
Zurückgehen in den getätigten Unitpropagations bis zum letzten branching
=> Wechsel der Variablen => Makieren als forced ('unitp')
=> Wenn erstes Element erreicht und erstes Element = Unitpropagation => CNF = unsatifiable
*/
void backtrack()
{
    for(int x = activities.size()-1; x>=0;x--)
    {
        if(activities[x].first=="unitp")
        {
            int s = activities[x].second;
            unset(s);
            activities.erase(activities.end());
            if(x==0) unsatisfiable=true;
        }
        else if(activities[x].first=="pureLit")
        {
            int s = activities[x].second;
            unset(s);
            activities.erase(activities.end());
            if(x==0) unsatisfiable=true;
        }
        else if(activities[x].first=="chooseLi")
        {
            int y=activities[x].second;
            unset(activities[x].second);
            activities.erase(activities.end());
            int m=-y;
            litSet(m);
            activities.push_back(make_pair("unitp",m));
            unit_propagation();
            handle_confilcts();
            break;
        }
    }
}

/*
Prüfen auf leere Klauseln
*/
bool check_conflicts()
{
    Clause *object;
    for(object=listc.begin();object!=0;object=object->next())
    {
        if(object->get_numberAct()==0)
        {
            return true;
        }
        else continue;
    }
    return false;
}

/*
Auswählen eines Literals 'li' aus der ersten, der kleinsten gefundenen Klauseln (!= Unitclauses)
Setzen des Wertes, den Literal hat in 'litSet'
*/
void set_val()
{
    Clause *object;
    int li;
    //Finden der kleinsten Klausel
    for(int i=2;i<=numVal;i++)
    {
        int ret=false;
        for(object=listc.begin();object!=0;object=object->next())
        {
            if(ret)break;
            else if(object->get_flag()==0)
            {
                int x = object->get_numberAct();
                if(x==i)
                {
                    int s = object->get_lit().size();
                    for (int j=0;j<s;j++)
                    {
                        int y= object->get_lit()[j];
                        int x;
                        if(y<0) x=(-1)*y;
                        else x=y;
                        if(find(listbel.begin(),listbel.end(),x)!=listbel.end()) continue;
                        else
                        {
                            li=y;
                            ret=true;
                            break;
                        }
                    }
                }
                else continue;
            }
            else continue;
        }
        if(ret) break;
    }
    litSet(li);
    activities.push_back(make_pair("chooseLi",li));
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
- unitpropagation in activities speichern
*/
void unit_propagation()
{
    Clause *object;
    int unitcl;
    //Finden von Clauses mit nur einem aktiven Literal
    for(object=listc.begin();object!=0;object=object->next())
    {
        if(object->get_numberAct()==1 && object->get_flag()==0)
        {
            //Finden des aktiven Literals: unitcl
            int s = object->get_lit().size();
            for (int j=0;j<s;j++)
            {
                int y= object->get_lit()[j];
                int z;
                if(y>0) z=y;
                else if(y<0) z=y*(-1);
                else break;
                if(find(listbel.begin(),listbel.end(),z)!=listbel.end())
                {
                    continue;
                }
                else
                {
                    unitcl=y;
                    break;
                }
            }
            activities.push_back(make_pair("unitp",unitcl)); //unitpropagation in activities speichern
            litSet(unitcl);
            object=listc.begin();
        }
        else continue;
    }
}

void litSet(int cl)
{
    int val; //Variable herausfinden: positive Zahl von unitcl (= val)
    if(cl<0) val=cl*(-1);
    else val=cl;
    //Gefundenes Literal in aktivierte Belegung speichern(listbel)
    listbel.push_back(val);
    Literal *objectl;
    for(objectl=listl.begin();objectl!=0;objectl=objectl->next())
    {
        if(objectl->get_nr()==val)
        {
            //cl = neg
            if(cl<0)
            {
                objectl->set_value(0);
                Clause *objectc;
                for(objectc=listc.begin();objectc!=0;objectc=objectc->next())
                {
                    if(objectc->get_flag()==0)
                    {
                        int x = objectc->get_nr();
                        //Finden von Caluses, in denen unitcl neg vor kommt
                        int s = objectl->get_neg().size();
                        for(int i=0;i<s;i++)
                        {
                            int y=objectl->get_neg()[i];
                            if(x==y)
                            {
                                objectc->set_flag(val); //clauses auf set u. Flag = val
                                setCl++;
                                break;
                            }
                            else continue;
                        }
                        //Finden von Clauses, in denen unitcl pos vor kommt.
                        s = objectl->get_pos().size();
                        for(int i=0;i<s;i++)
                        {
                            int y=objectl->get_pos()[i];
                            if(x==y)
                            {
                                objectc->set_numberAct(-1); //aktive lit in clauses -1
                            }
                            else continue;
                        }
                    }
                    else continue;
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
                    int z=objectc->get_flag();
                    if(z==0)
                    {
                        int x = objectc->get_nr();
                        //Finden von Clauses, in denen unitcl pos vor kommt.
                        int s = objectl->get_pos().size();
                        for(int i=0;i<s;i++)
                        {
                            int y=objectl->get_pos()[i];
                            if(x==y)
                            {
                                objectc->set_flag(val);//clauses auf set u. Flag = val
                                setCl++;
                            }
                            else continue;
                        }
                        //Finden von Caluses, in denen unitcl neg vor kommt
                        s = objectl->get_neg().size();
                        for(int i=0;i<s;i++)
                        {
                            int y=objectl->get_neg()[i];
                            if(x==y)
                            {
                                objectc->set_numberAct(-1); //aktive lit in clauses -1
                            }
                            else continue;
                        }
                    }
                    else continue;
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
                    if(numVal>99)
                    {
                        line[0] = ' ';
                        line[1] = ' ';
                        line[2] = ' ';
                        line = stAdjust (line);
                    }
                    else if(numVal > 9)
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
                for (int i=1;i<=numVal; i++)
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
                    object->set_neg(c);
                }
                else if(l>0)
                {
                    object->set_pos(c);
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

//Return (string s, bool *error)
int retIntFromString (string s, bool *error)
{
    char c;
    int state = 0;
    int vsign;
    int val;
    int sl = s.length();
    for (int i=0; i< sl; i++)
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
                int x = atoi(&c);
                val=10*val +x;
                state=3;
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
        else if(state ==3) //second digit read
        {
           if(c>='0' && c<='9') //third digit
            {
                int x = atoi(&c);
                val=10*val +x;
                val=vsign*val;
                return val;
            }
            else if (c==' ')
            {
                val = vsign*val;
                return val;
            }
            else
            {
                cout << "vierter error" << endl;
                *error = true;
                return 0;
            }
        }
        else
        {
            cout << "fünfter error" << endl;
            *error = true;
            return 0;
        }
    }
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

    int s = s2.length();
    for ( i = 0; i < s; i++ )
    {
        if ( s1[i] != ' ' && s1[i] != TAB )
        {
            nonblank = i;
            break;
        }
    }
    if ( 0 < nonblank )
    {
        int s = s2.length();
        int sp = s2.length() - nonblank;
        for ( i = 0; i < sp; i++ )
        {
            s2[i] = s1[i+nonblank];
        }
        for ( i = sp; i < s; i++ )
        {
            s2[i] = ' ';
        }

    }
    return s2;
}


