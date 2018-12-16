/***************************************************************
 * Name:      Projekt2Main.cpp
 * Purpose:   Code for Application Frame
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

#include "Projekt2Main.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


Projekt2Frame::Projekt2Frame(wxFrame *frame)
    : GUIFrame(frame)
{
#if wxUSE_STATUSBAR
    statusBar->SetStatusText(_("DPLL SAT Solver by Andrea Kuchar"), 0);
    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
#endif
}

Projekt2Frame::~Projekt2Frame()
{
}

void Projekt2Frame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void Projekt2Frame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void Projekt2Frame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
