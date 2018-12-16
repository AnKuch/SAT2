/***************************************************************
 * Name:      Projekt2App.h
 * Purpose:   Defines Application Class
 * Author:    Andrea Kuchar ()
 * Created:   2018-12-15
 * Copyright: Andrea Kuchar ()
 * License:
 **************************************************************/

#ifndef PROJEKT2APP_H
#define PROJEKT2APP_H

#include <wx/app.h>
#include "FileRead.h"

class Projekt2App : public wxApp
{
    public:
        virtual bool OnInit();
};
list<int> solve(string, string);

#endif // PROJEKT2APP_H
