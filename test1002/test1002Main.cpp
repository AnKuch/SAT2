/***************************************************************
 * Name:      test1002Main.cpp
 * Purpose:   Code for Application Frame
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

#include "test1002Main.h"

// Initialisierung der Applikation
IMPLEMENT_APP(MainApp);


// Implementierung der "main()" Klasse für das Hauptfenster
bool MainApp::OnInit()
{
	SetTopWindow( new MainFrame( NULL ) );
	GetTopWindow()->Show();
	return true;
}


// Implementierung des Hauptfensters bzw. des Einstiegsfensters
// Es ist geschickter in der main() Funktion von MainFrameBase zu programmieren,
// da man das konkrete Fenster verändert und nicht ein Fenster-Pointer
MainFrame::MainFrame(wxWindow *parent) : MainFrameBase( parent )
{
}

MainFrame::~MainFrame()
{
}

mf::mf(wxWindow *parent) : mfb( parent )
{
}

mf::~mf()
{
}


void mf::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void mf::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}


void MainFrame::OnCloseFrame(wxCloseEvent& event)
{
	Destroy();
}

void MainFrame::OnExitClick(wxCommandEvent& event)
{
	Destroy();
}
