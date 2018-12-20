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

#include "GUIFrame.h"
#include "wx/wx.h"
#include "wx/wxprec.h"
#include <wx/textfile.h>
#include "test1002App.h"
#include "vector"
#include <wx/clipbrd.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/wfstream.h>


std::string newPuzzle ="";
long wexeb1 = wxNewId();

wxTextCtrl *eb ;
wxTextCtrl *eb2 ;


// Implementierung der main() des Ausgabefensters
mfb::mfb( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{

	this->SetSize(1000,1000);
	this->Centre( wxBOTH );

}


// Implementierung der main() des Hauptfensters
MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{

	long wex = wxNewId();
	long wexb1 = wxNewId();
	long wexb2 = wxNewId();

	this->SetSize(1000,1000);

	// Fenstererweiterungen(Menu, Buttons, Textfeld etc...)
	CreateStatusBar(3);
    SetStatusText(wxT("DPLL Solver"), 0);
	menuBar = new wxMenuBar();
	menu = new wxMenu();
	menu->Append(wxID_OPEN,_T("&Open"));
	menu->Append(wxID_OPEN,_T("&New"));
	menu->AppendSeparator();
	menu->Append(wex,_T("E&xit"));
	menuBar->Append(menu,_T("&Solver"));
	SetMenuBar(menuBar);

	wxButton *wbOP = new wxButton(this, wexb1, _T("Open and solve a SAT instance"),wxPoint(50, 200),wxSize(220,220), 0);
	wxButton *wbOP1 = new wxButton(this, wexb2, _T("Solve the new instance"),wxPoint(50, 400),wxSize(220,220), 0);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(wexb1,1,wxEXPAND | wxALL,5);
	vbox->Add(wexb2,1,wxEXPAND | wxALL,5);
	eb = new wxTextCtrl(this,wexeb1," Enter a new SAT instance in DIMACS CNF format",wxPoint(400,80), wxSize(500,500),  wxTE_MULTILINE | wxTE_RICH |wxHSCROLL, wxDefaultValidator,wxTextCtrlNameStr);
	vbox->Add(wexeb1,1,wxEXPAND | wxALL,5);
	this->SetSizer(vbox);


	// Events an eine Funktion knüpfen
	this->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainFrameBase::NewFile, this, wexb2);
	this->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&MainFrameBase::OpenFile, this, wexb1);
	this->Bind(wxEVT_MENU,&MainFrameBase::OpenFile, this, wxID_OPEN);
	this->Bind(wxEVT_MENU,&MainFrameBase::OnClose, this, wex);


	this->Centre( wxBOTH );

}


// Eingebenes Puzzle wird eingelesen und gelöst
void MainFrameBase::NewFile(wxCommandEvent& WXUNUSED(event)){

	wxString dir ;
	wxString filename;
	wxFileDialog *OD = new wxFileDialog(this, _("Select a file to save your formular."), "", "","XYZ files (*.cnf)|*.cnf",wxFD_SAVE);
	eb->Refresh();
	if (OD->ShowModal() == wxID_CANCEL)
	   return;

	dir = OD->GetDirectory() ;
	std::string sdir = dir.ToStdString();
	std::string sfilename = "Temp.txt";
	eb->SaveFile(_T("Temp.txt"),0);
	string result;
	std::vector<int> pb = solver(sfilename,sdir,&result);
	if (pb.empty()) {
	   wxMessageBox("Error : Empty result from picosat", "ERROR", wxOK | wxICON_INFORMATION);
	   return ;
	}

	 // Falls die Instanz erfolgreich gelöst wurde, die Lösung ausgegeben
	std::ostringstream st;
	for (int i = (pb.size())-1; i>=0;i--)
    {
        st << pb[i] << ' ' << ' ';
    }
    wxMessageBox(st.str().c_str(),"Solution");


	return;
}


// Fenster schließen
void MainFrameBase::OnClose(wxCommandEvent& WXUNUSED(event)) {
	Destroy();
}


// Öffnen einer .cnf Datei
void MainFrameBase::OpenFile(wxCommandEvent& WXUNUSED(event))
{
	wxString  filename;
	wxString wxdir ;
	wxFileDialog *OpenDialog = new wxFileDialog(this, _("Open a Puzzle"), "", "","XYZ files (*.cnf)|*.cnf", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
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

    // Aufruf der solver() Funktion um das Puzzle zu lösen
	std::string sdir = wxdir.ToStdString();
	std::string sfilename = filename.ToStdString();
	std::string result;
	std::vector<int> pb = solver(sfilename,sdir,&result);
	if (pb.empty()) {
	   wxMessageBox("Error : Empty result", "ERROR", wxOK | wxICON_INFORMATION);
	   return ;
	}

	// Falls die Instanz erfolgreich gelöst wurde, die Lösung ausgegeben
	std::ostringstream st;
	for (int i = (pb.size())-1; i>=0;i--)
    {
        st << pb[i] << ' '  << ' ';
    }
    wxMessageBox(st.str().c_str(),"Solution");



return;


}


// Zeichnen der Puzzlelösung in einem neuen Fenster
void mfb::ColPanel(std::vector<int> pb){
    long w = wxNewId();
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    wxWindow *mf1 = new mfb( NULL,  w, wxEmptyString,  wxDefaultPosition,  wxSize( 500,300 ),  wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
    long wex = wxNewId();
    wxPanel *panel = new wxPanel(this, -1);

    CreateStatusBar(3);
    SetStatusText(wxT("DPLL Solver"), 0);
	menuBar = new wxMenuBar();
	menu = new wxMenu();
	menu->Append(wxID_OPEN,_T("&Open"));
	menu->AppendSeparator();
	menu->Append(wex,_T("E&xit"));

    eb2 = new wxTextCtrl(this,wexeb1," Enter a new SAT instance in DIMACS CNF format",wxPoint(400,80), wxSize(500,500),  wxTE_MULTILINE | wxTE_RICH |wxHSCROLL, wxDefaultValidator,wxTextCtrlNameStr);
	vbox->Add(wexeb1,1,wxEXPAND | wxALL,5);
	mf1->SetSizer(vbox);
    mf1->Show();

//long wex = wxNewId();
//	long wexb1 = wxNewId();
//	long wexb2 = wxNewId();
//
//	this->SetSize(1000,1000);
//
//	// Fenstererweiterungen(Menu, Buttons, Textfeld etc...)
//	CreateStatusBar(3);
//    SetStatusText(wxT("DPLL Solver"), 0);
//	menuBar = new wxMenuBar();
//	menu = new wxMenu();
//	menu->Append(wxID_OPEN,_T("&Open"));
//	menu->AppendSeparator();
//	menu->Append(wex,_T("E&xit"));
//
//	SetMenuBar(menuBar);
//
//
//	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//	vbox->Add(wexb1,1,wxEXPAND | wxALL,5);
//	vbox->Add(wexb2,1,wxEXPAND | wxALL,5);
//	std::stringstream out;
//    for (int i = 1; i<pb.size(); i++)
//    {
//		int k = pb[i];
//		out << k << ' ';
//	}
//	string outs= out.str();
//	eb = new wxTextCtrl(this,wexeb1,outs,wxPoint(400,80), wxSize(500,500),  wxTE_MULTILINE | wxTE_RICH |wxHSCROLL, wxDefaultValidator,wxTextCtrlNameStr);
//	vbox->Add(wexeb1,1,wxEXPAND | wxALL,5);
//	this->SetSizer(vbox);
//
//
//	// Events an eine Funktion knüpfen
//
//	this->Bind(wxEVT_MENU,&MainFrameBase::OnClose, this, wex);
//
//
//	this->Centre( wxBOTH );


//	long w = wxNewId();
//	wxWindow *mf1 = new mfb( NULL,  w, wxEmptyString,  wxDefaultPosition,  wxSize( 500,300 ),  wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL);
//	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
//    wxFlexGridSizer *fgs = new wxFlexGridSizer(1, 2, 0,0);
//    fgs->AddGrowableRow(0) ;
//    fgs->AddGrowableCol(0);
//    int r = pb[pb.size()-1];
//    int c = pb[pb.size()-2];
//    int l = r*c;
//    wxGridSizer *gs = new wxGridSizer(r, c, 0,0);
//
//    std::stringstream out;
//    for (int i = 1; i<=l; i++)
//    {
//		int k = pb[i];
//		out << k << ' ';
//	}
//	string outs= out.str();
//	eb2 = new wxTextCtrl(this,wexeb1,outs,wxPoint(400,80), wxSize(500,500),  wxTE_MULTILINE | wxTE_RICH |wxHSCROLL, wxDefaultValidator,wxTextCtrlNameStr);
//    fgs->Add(gs,1,wxEXPAND| wxALL, 5 );
//    vbox->Add(fgs,1,wxEXPAND | wxALL, 5);
//    mf1->SetSizer(vbox);
//    mf1->Show();

return;
}


MainFrameBase::~MainFrameBase()
{

}
mfb::~mfb()
{

}
