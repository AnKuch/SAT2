///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 17 2007)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////
BEGIN_EVENT_TABLE( GUIFrame, wxFrame )
    EVT_CLOSE( GUIFrame::_wxFB_OnClose )
    EVT_MENU( idMenuQuit, GUIFrame::_wxFB_OnQuit )
    EVT_MENU( idMenuAbout, GUIFrame::_wxFB_OnAbout )
END_EVENT_TABLE()

GUIFrame::GUIFrame( wxWindow* parent, int id, wxString title, wxPoint pos, wxSize size, int style ) : wxFrame( parent, id, title, pos, size, style )
{
    long wex = wxNewId();
	long wexb1 = wxNewId();
	long wexb2 = wxNewId();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    mbar = new wxMenuBar( 0 );
    wxMenu* fileMenu;
    fileMenu = new wxMenu();
    wxMenuItem* menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( wxT("&Quit") ) + wxT('\t') + wxT("Alt+F4"), wxT("Quit the application"), wxITEM_NORMAL );
    fileMenu->Append( menuFileQuit );
    mbar->Append( fileMenu, wxT("&File") );
    wxMenu* helpMenu;
    helpMenu = new wxMenu();
    wxMenuItem* menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( wxT("&About") ) + wxT('\t') + wxT("F1"), wxT("Show info about this application"), wxITEM_NORMAL );
    helpMenu->Append( menuHelpAbout );
    mbar->Append( helpMenu, wxT("&Help") );
    this->SetMenuBar( mbar );

    statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
    wxButton *wbOP = new wxButton(this, wexb1, _T("Open predefined cnf file"),wxPoint(25, 100),wxSize(190,70), 0);
    wxButton *wbOP1 = new wxButton(this, wexb2, _T("Input a new SAT instance as DIMACS CNF format"),wxPoint(25, 200),wxSize(380,70), 0);

    //Events an Funktion knüpfen
    this->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&GUIFrame::OpenFile, this, wexb1);
}


// Öffnen einer .cnf Datei
void GUIFrame::OpenFile(wxCommandEvent& WXUNUSED(event))
{
    wxString  filename;
	wxString wxdir ;
	wxFileDialog *OpenDialog = new wxFileDialog(this, _("Open a .cnf file"), "", "","XYZ files (*.cnf)|*.cnf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
	//OpenDialog->ShowModal();
	if (OpenDialog->ShowModal() == wxID_OK)
	{
	   wxdir.clear();
	   filename.clear();
	   filename = OpenDialog->GetPath();
	   wxdir = OpenDialog->GetDirectory();
	}
	else {
	   return;
	   }


	std::string dir = wxdir.ToStdString();
	std::string sfilename = filename.ToStdString();

    if(solve(sfilename,dir)=={})
    {
        wxMessageBox("Error ", "ERROR", wxOK | wxICON_INFORMATION);
        return ;
    }
    else
    {
        wxMessageBox("Yeah ", "ERROR", wxOK | wxICON_INFORMATION);
        return ;
    }
    return;
}
