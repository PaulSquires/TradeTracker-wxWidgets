#include <wx/wx.h>

#include "TabPanel.h"

TabPanel::TabPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(100,100,200));
    new wxStaticText(this, wxID_ANY, "TabPanel");

    wxButton* btn_active_trades = new wxButton(this, wxID_ANY, "Active");
	btn_active_trades->Bind(wxEVT_BUTTON, &TabPanel::ActiveTradesClicked, this);
}


void TabPanel::ActiveTradesClicked(wxCommandEvent& event) {
    wxLogDebug("Clicked");

    event.Skip();
}

