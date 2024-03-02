#include <wx/wx.h>

#include "TradeHistory.h"

TradeHistory::TradeHistory(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(100,200,100));
    new wxStaticText(this, wxID_ANY, "TradeHistory");
}
