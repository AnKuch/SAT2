/***************************************************************
 * Name:      test1002App.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2018-11-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TEST1002APP_H
#define TEST1002APP_H

#include <wx/app.h>

#include <iostream>
#include <fstream>
#include <vector>
#include "Clauselist.h"
#include "Literallist.h"
#include <chrono>
#include <algorithm>
#include <sstream>

using namespace std;

std::vector<int> solver(string,string,string *);
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


std::vector<int> clsol(std::string filename,std::string dir);
std::string oneOnEach (int zeilen, int spalten);
int zeilenSpalten (std::string);
char setVariables (std::string);
std::string sameRo(int, int);
std::string sameCo(int, int);
std::string getInput(std::string filename, int fl);

#endif //TEST1002APP_H
