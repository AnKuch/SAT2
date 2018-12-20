///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFrame__
#define __GUIFrame__

// Define WX_GCH in order to support precompiled headers with GCC compiler.
// You have to create the header "wx_pch.h" and include all files needed
// for compile your gui inside it.
// Then, compile it and place the file "wx_pch.h.gch" into the same
// directory that "wx_pch.h".
#ifdef WX_GCH
#include <wx_pch.h>
#else
#include <wx/wx.h>
#endif

#include "wx/wxprec.h"
#include <wx/textfile.h>
#include "test1002App.h"
#include "vector"
#include <wx/clipbrd.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>


///////////////////////////////////////////////////////////////////////////

#define idMenuQuit 1000
#define idMenuAbout 1001

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame
{
	private:

	protected:
		wxMenuBar* menuBar;
		wxMenu* menu;
		wxStatusBar* m_statusBar;

		// Default Definitionen von Event Handler
		virtual void OnCloseFrame( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnExitClick( wxCommandEvent& event ) { event.Skip(); }


public:

		// MainFrameBase ist der eigentliche Konstruktor
		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void OpenFile(wxCommandEvent& WXUNUSED(event));
		void OnClose(wxCommandEvent& WXUNUSED(event));
		void NewFile(wxCommandEvent& WXUNUSED(event));
		~MainFrameBase();

};


// Klasse mfb
class mfb : public wxFrame {
		private:

	protected:
		wxMenuBar* menuBar;
		wxMenu* menu;
		wxStatusBar* m_statusBar;
		wxTextCtrl *textctrl;


public:

		// mfb ist der eigentliche Konstruktor
		mfb( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void ColPanel(std::vector<int> pb);
		void OpenFile(wxCommandEvent& WXUNUSED(event));
		void OnClose(wxCommandEvent& WXUNUSED(event));
		void NewFile(wxCommandEvent& WXUNUSED(event));
		~mfb();

};






#endif //__GUIFrame__
