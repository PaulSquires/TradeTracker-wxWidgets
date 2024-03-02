#include <wx/wx.h>

#include "TabPanel.h"

TabPanel::TabPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
    const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(100,100,200));
    new wxStaticText(this, wxID_ANY, "TabPanel");
}
