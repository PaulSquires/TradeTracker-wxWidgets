#include <wx/wx.h>
#include <wx/splitter.h>

#include "MainWindow.h"

MainWindow::MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    wxPanel* left_panel = new wxPanel(splitter);
    wxPanel* right_panel = new wxPanel(splitter);

    left_panel->SetBackgroundColour(wxColor(200,100,100));
    right_panel->SetBackgroundColour(wxColor(100,200,100));

    splitter->SetMinimumPaneSize(wxWindow::FromDIP(200));
    splitter->SetSashGravity(1);
    splitter->SplitVertically(left_panel, right_panel);


    wxPanel* bottom_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxWindow::FromDIP(wxSize(200,100)));
    bottom_panel->SetBackgroundColour(wxColor(100,100,200));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(splitter, 1, wxEXPAND);
    sizer->Add(bottom_panel, 0, wxEXPAND);

    this->SetSizerAndFit(sizer);
}
