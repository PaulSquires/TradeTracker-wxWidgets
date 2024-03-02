#include <wx/wx.h>

#include "ClosedTrades.h"

ClosedTrades::ClosedTrades(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(200,100,100));
    new wxStaticText(this, wxID_ANY, "ClosedTrades");
}
