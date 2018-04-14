// -*- C++ -*-
//
// generated by wxGlade 0.8.0 on Fri Apr 13 20:59:07 2018
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#include "MatStore.h"
#include "dialog.h"

// begin wxGlade: ::extracode
// end wxGlade

MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
	wxFrame(parent, id, title, pos, size, wxBORDER_SIMPLE|wxCAPTION|wxCLIP_CHILDREN|wxCLOSE_BOX|wxFRAME_FLOAT_ON_PARENT|wxFRAME_TOOL_WINDOW|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxSTAY_ON_TOP|wxSYSTEM_MENU)
{
	// begin wxGlade: MyFrame::MyFrame
	btnStore = new wxButton(this, wxID_ANY, wxT("Store"));
	btnRestore = new wxButton(this, wxID_ANY, wxT("Restore"));
	btnSave = new wxButton(this, wxID_ANY, wxT("Save"));
	btnLoad = new wxButton(this, wxID_ANY, wxT("Load"));
	label_1 = new wxStaticText(this, wxID_ANY, wxEmptyString);
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MyFrame::OnExit));
	set_properties();
	do_layout();
	// end wxGlade
}

void MyFrame::OnExit(wxCloseEvent & WXUNUSED)
{
	MatStore::GetInstance().SetVisible(false);
}


void MyFrame::set_properties()
{
	// begin wxGlade: MyFrame::set_properties
	SetTitle(wxT("MatStore"));
	// end wxGlade
}


void MyFrame::do_layout()
{
	// begin wxGlade: MyFrame::do_layout
	wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(6, 3, 0, 0);
	sizer_2->Add(0, 5, 0, 0, 0);
	grid_sizer_1->Add(5, 0, 0, wxEXPAND, 0);
	grid_sizer_1->Add(btnStore, 0, wxALIGN_CENTER, 0);
	grid_sizer_1->Add(5, 0, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(btnRestore, 0, wxALIGN_CENTER, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	wxStaticLine* static_line_2 = new wxStaticLine(this, wxID_ANY);
	grid_sizer_1->Add(static_line_2, 0, wxBOTTOM|wxEXPAND|wxTOP, 5);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(btnSave, 0, wxALIGN_CENTER, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(btnLoad, 0, wxALIGN_CENTER, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	grid_sizer_1->Add(label_1, 0, 0, 0);
	grid_sizer_1->Add(0, 0, 0, 0, 0);
	sizer_2->Add(grid_sizer_1, 0, wxBOTTOM|wxTOP, 5);
	SetSizer(sizer_2);
	sizer_2->Fit(this);
	sizer_2->SetSizeHints(this);
	Layout();
	// end wxGlade
}


class MyApp: public wxApp {
public:
	bool OnInit();
};

//IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxInitAllImageHandlers();
	MyFrame* frame = new MyFrame(NULL, wxID_ANY, wxEmptyString);
	SetTopWindow(frame);
	frame->Show();
	return true;
}