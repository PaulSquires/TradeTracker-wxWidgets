#include <wx/wx.h>
#include <wx/splitter.h>

#include "ActiveTrades.h"
#include "TradeHistory.h"
#include "TabPanel.h"
#include "MainWindow.h"

MainWindow::MainWindow(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    splitter = new wxSplitterWindow(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    left_panel = new ActiveTrades(splitter);
    right_panel = new TradeHistory(splitter);
    bottom_panel = new TabPanel(this, wxID_ANY, wxDefaultPosition, wxWindow::FromDIP(wxSize(200,100)));

    splitter->SetMinimumPaneSize(wxWindow::FromDIP(200));
    splitter->SetSashGravity(1);
    splitter->SplitVertically(left_panel, right_panel);

    sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(splitter, 1, wxEXPAND);
    sizer->Add(bottom_panel, 0, wxEXPAND);

    this->SetSizerAndFit(sizer);
}
