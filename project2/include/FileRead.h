#ifndef FILEREAD_H
#define FILEREAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "main.h"

using namespace std;

bool cnfRead(std::string);
int lastblank (std::string );
std::string stAdjust (std::string);
void extractFirst (std::string, string &s1, string &s2);
int lengNonBl (std::string);
int retIntFromString (std::string s, int *last, bool *error);



#endif // FILEREAD_H
