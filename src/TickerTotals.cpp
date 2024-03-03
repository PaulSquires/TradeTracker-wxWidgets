#include <wx/wx.h>

#include "TickerTotals.h"

TickerTotals::TickerTotals(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(100,200,100));
    new wxStaticText(this, wxID_ANY, "TickerTotals");
}
