#include <wx/wx.h>

#include "TradePlan.h"

TradePlan::TradePlan(wxWindow* parent, wxWindowID id, const wxPoint& pos,
		const wxSize& size, long style, const wxString& name)
    : wxPanel(parent, id, pos, size, style, name)
{
    this->SetBackgroundColour(wxColor(200,100,100));
}
