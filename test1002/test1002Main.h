/***************************************************************
 * Name:      test1002Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2018-11-28
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef TEST1002MAIN_H
#define TEST1002MAIN_H



#include "test1002App.h"


#include "GUIFrame.h"

#include <wx/wx.h>


// Deklaration der Applikationsklasse ; OnInit() ist wie eine klassische main() Funktion
class MainApp : public wxApp
{
	public:
		virtual bool OnInit();
};


// Deklaration der globalen statischen Funktion wxGetApp() ; Ansonsten ist keine Visualiserung möglich
DECLARE_APP(MainApp)


// Klassischer Teil eines Header
// Klasse des Hauptfensters
class MainFrame : public MainFrameBase
{
	public:
		MainFrame( wxWindow *parent );
		MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
		virtual ~MainFrame();
	protected:

		// Event Handler
		virtual void OnCloseFrame( wxCloseEvent& event );
		virtual void OnExitClick( wxCommandEvent& event );
};


// Klasse des Ausgabefensters
class mf : public mfb
{
	public:
		mf( wxWindow *parent );
		mf( const wxString &title, const wxPoint &pos, const wxSize &size );
		virtual ~mf();
	protected:

		// Event Handler
		virtual void OnCloseFrame( wxCloseEvent& event );
		virtual void OnExitClick( wxCommandEvent& event );
};


#endif // TEST1002MAIN_H
