/***************************************************************
 * Name:      Projekt2App.cpp
 * Purpose:   Code for Application Class
 * Author:    Andrea Kuchar ()
 * Created:   2018-12-15
 * Copyright: Andrea Kuchar ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Projekt2App.h"
#include "Projekt2Main.h"
#include <string>
#include <cstdlib>
#include <list>
#include <fstream>

using namespace std;

IMPLEMENT_APP(Projekt2App);

bool Projekt2App::OnInit()
{
    Projekt2Frame* frame = new Projekt2Frame(0L);

    frame->Show();

    return true;
}

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
    int get_nr(){return number;}

    Literal *next(){return suc;}
};

class Literallist
{
private:
    Literal *start;
public:
    Literallist()
    {
        start = 0;
    }
    Literal *begin(){return start;}
    void insert(Literal *k)
	{
		k->suc = start;
		start = k;
	}
	Literal* findl(int nam)
	{
		Literal *fin;
		for (fin = begin(); fin != 0; fin = fin->next())
			if (fin->get_nr() == nam)
				break;
		return fin;
	}
	void remove(int nam)
	{
		if(start!=NULL)
		{
			if(start->get_nr() == nam)
            {
				start = start->next();
			}
			else if(start->get_nr() != nam && start->next() == NULL)
			{
				return;
			}
			else
			{
				Literal *fin;
				for (fin = begin(); fin != 0; fin = fin->next())
				{
					if(fin->next()->get_nr() != nam && fin->next()->next() == NULL)
						break;
					else if (fin->next()->get_nr() == nam)
                    {
                        fin->suc = fin->next()->next();
						break;
					}
				}
			}
		}
	}
	bool empty() { return start == 0; }
};

class Clause
{
friend class Clauselist;
private:
    int number;
    Literallist x;
    Clause *suc;
public:
    Clause(Literallist a, int b): x(a), number(b)
    {
        suc = 0;
    }
    Clause *next(){return suc;}
    int get_nr(){return number;}
    Literallist get_lit(){return x;}
};

class Clauselist
{
private:
    int counter;
    Clause *start;
public:
    Clauselist()
    {
        start=0;
    }
    Clause *begin(){return start;}
    void insert(Clause *k)
	{
		k->suc = start;
		start = k;
	}
	Clause* findl(int nam)
	{
		Clause *fin;
		for (fin = begin(); fin != 0; fin = fin->next())
			if (fin->get_nr() == nam)
				break;
		return fin;
	}
	void remove(int nam)
	{
		if(start!=NULL)
		{
			if(start->get_nr() == nam)
            {
				start = start->next();
			}
			else if(start->get_nr() != nam && start->next() == NULL)
			{
				return;
			}
			else
			{
				Clause *fin;
				for (fin = begin(); fin != 0; fin = fin->next())
				{
					if(fin->next()->get_nr() != nam && fin->next()->next() == NULL)
						break;
					else if (fin->next()->get_nr() == nam)
                    {
                        fin->suc = fin->next()->next();
						break;
					}
				}
			}
		}
	}
	bool empty() { return start == 0; }
};

list<int> solve(string fname, string path)
{
    ifstream file;
    file.open(fname, ios_base::in);
    if (!file) // Datei konnte nicht geöffnet werden
    {
        cout << "File couldn't be read." << endl;
        return {};
    }
    else
    {
        return {1};
    }
}

list<int> setLit;
list<int> DPLL(Clauselist *,int, int);

list<int> DPLL(Clauselist *cl,int l, int c)
{
    int litcounter = l;
    int clcounter = c;
    Clause *object;
    if(cl->empty())
    {
        return setLit;
    }
    else
    {
        for(object=cl->begin();object!=0;object=object->next())
        {
            if(object->get_lit().begin()->next()==0)
            {
                int y = object->get_lit().begin()->get_nr();
                setLit.push_back(y);
            }
        }
    }
}
