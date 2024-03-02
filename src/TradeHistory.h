#ifndef SRC_TRADEHISTORY_H
#define SRC_TRADEHISTORY_H

#include <wx/wx.h>

class TradeHistory : public wxPanel {
public:
    TradeHistory( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,	long style = wxTAB_TRAVERSAL, const wxString& name = wxPanelNameStr );

};


#endif  /* SRC_TRADEHISTORY_H */
