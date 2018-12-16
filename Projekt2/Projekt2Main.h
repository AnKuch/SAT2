/***************************************************************
 * Name:      Projekt2Main.h
 * Purpose:   Defines Application Frame
 * Author:    Andrea Kuchar ()
 * Created:   2018-12-15
 * Copyright: Andrea Kuchar ()
 * License:
 **************************************************************/

#ifndef PROJEKT2MAIN_H
#define PROJEKT2MAIN_H



#include "Projekt2App.h"


#include "GUIFrame.h"

class Projekt2Frame: public GUIFrame
{
    public:
        Projekt2Frame(wxFrame *frame);
        ~Projekt2Frame();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};

#endif // PROJEKT2MAIN_H
