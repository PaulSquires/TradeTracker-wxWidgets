#ifndef SRC_TRADEPLAN_H
#define SRC_TRADEPLAN_H

#include <wx/wx.h>

class TradePlan : public wxPanel {
public:
    TradePlan( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_TRADEPLAN_H */
